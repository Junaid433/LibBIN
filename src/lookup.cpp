#include "lookup.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <cctype>

namespace LibBIN {

static std::unordered_map<std::string, Result> bin_map;
static bool bins_loaded = false;
static std::mutex load_mutex;

void Lookup::load_bins(const std::string& csv_path) {
    std::lock_guard<std::mutex> lock(load_mutex);
    if (bins_loaded) return;

    std::ifstream file(csv_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open BIN CSV file: " << csv_path << "\n";
        return;
    }

    std::string line;
    std::getline(file, line);
    auto trim_quotes = [](const std::string& s) -> std::string {
        if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
            return s.substr(1, s.size() - 2);
        return s;
    };

    bin_map.clear();
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> fields;
        while (std::getline(ss, token, ',')) {
            fields.push_back(trim_quotes(token));
        }
        if (fields.size() < 7) continue;

        Result r{};
        r.bin = fields[0];
        r.country = fields[1];
        r.scheme = fields[3];
        r.type = fields[4];
        r.brand = fields[5];
        r.bank = fields[6];
        r.is_valid = !r.bin.empty() && !r.country.empty();

        bin_map[r.bin] = std::move(r);
    }
    bins_loaded = true;
}

const std::unordered_map<std::string, Result>& Lookup::get_bin_map() {
    return bin_map;
}

bool Lookup::is_valid_bin(std::string_view bin) {
    if (bin.size() < 6 || bin.size() > 8) return false;
    for (char c : bin) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

auto Lookup::Search(std::string_view bin) -> std::expected<Result, LookupError> {
    if (!bins_loaded) {
        return std::unexpected{LookupError("BIN database not loaded. Call load_bins() first.")};
    }
    if (!is_valid_bin(bin)) {
        return std::unexpected{InvalidFormatError{std::string(bin)}};
    }
    auto it = bin_map.find(std::string(bin));
    if (it == bin_map.end()) {
        return std::unexpected{NotFoundError{std::string(bin)}};
    }
    return it->second;
}
} 
