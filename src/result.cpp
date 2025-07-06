#include "result.hpp"
#include <format>

namespace LibBIN {
    auto Result::summary() const -> std::string {
        return std::format(
            "BIN: {}\nScheme: {}\nType: {}\nBrand: {}\nBank: {}\nCountry: {} ({})\nLevel: {}\nFlag: {}\nPrepaid: {}\nValid: {}",
            bin,
            scheme,
            type,
            brand,
            bank,
            country,
            country_code,
            level,
            country_flag,
            prepaid ? "Yes" : "No",
            is_valid ? "Yes" : "No"
        );
    }
}
