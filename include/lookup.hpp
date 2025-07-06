#pragma once

#include <string_view>
#include <string>
#include <expected>
#include <unordered_map>
#include "result.hpp"
#include "errors.hpp"

namespace LibBIN {
    class Lookup {
        public:
            static void load_bins(const std::string& csv_path = "data/bin_data.csv");
            static auto Search(std::string_view bin) -> std::expected<Result, LookupError>;

        private:
            static const std::unordered_map<std::string, Result>& get_bin_map();
        static bool is_valid_bin(std::string_view bin);
    };
}
