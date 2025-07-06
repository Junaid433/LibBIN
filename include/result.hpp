#pragma once

#include <string>
#include <string_view>

namespace LibBIN{
    struct Result{
      std::string bin;
      std::string scheme;
      std::string type;
      std::string brand;
      std::string bank;
      std::string country;
      std::string country_code;
      std::string level;
      std::string country_flag;
      bool prepaid = false;
      bool is_valid = true;
      [[nodiscard]] auto summary() const -> std::string;
    };
}