#include <benchmark/benchmark.h>
#include "lookup.hpp"
#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> 

using namespace LibBIN;

static const std::vector<std::string> sample_bins = {
    "100100", "100101", "100102", "100103", "100104", "100105"
};

static std::string random_sample_bin() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, sample_bins.size() - 1);
    return sample_bins[dist(rng)];
}

static void BM_Lookup_SameBin(benchmark::State& state) {
    for (auto _ : state) {
        auto result = Lookup::Search("100101");
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Lookup_RandomBin(benchmark::State& state) {
    for (auto _ : state) {
        auto bin = random_sample_bin();
        auto result = Lookup::Search(bin);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Lookup_InvalidBin(benchmark::State& state) {
    for (auto _ : state) {
        auto result = Lookup::Search("xyzabc");
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Lookup_NotFound(benchmark::State& state) {
    for (auto _ : state) {
        auto result = Lookup::Search("000000");
        benchmark::DoNotOptimize(result);
    }
}

static void BM_LoadBinsOnce(benchmark::State& state) {
    for (auto _ : state) {
        std::ifstream file("data/bin_data.csv");
        benchmark::DoNotOptimize(file);
        std::unordered_map<std::string, Result> map;
        std::string line;
        std::getline(file, line);
        auto trim_quotes = [](const std::string& s) -> std::string {
            if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
                return s.substr(1, s.size() - 2);
            return s;
        };
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
            map[r.bin] = std::move(r);
        }
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_Lookup_SameBin);
BENCHMARK(BM_Lookup_RandomBin);
BENCHMARK(BM_Lookup_InvalidBin);
BENCHMARK(BM_Lookup_NotFound);
BENCHMARK(BM_LoadBinsOnce);
BENCHMARK_MAIN();
