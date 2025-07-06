#pragma once 

#include <string_view>
#include <string>
#include <format>
#include <exception>

namespace LibBIN {
    class LookupError : public std::exception {
        public:
            explicit LookupError(std::string_view message) : msg_(std::string(message)) {}
            [[nodiscard]] const char* what() const noexcept override {
                return msg_.c_str();
            }
        private:
            std::string msg_;
        };
    class NotFoundError : public LookupError {
        public:
            explicit NotFoundError(std::string_view bin)
                : LookupError(std::format("BIN not found: {}", bin)) {}
        };
    class InvalidFormatError : public LookupError {
        public:
            explicit InvalidFormatError(std::string_view bin)
                : LookupError(std::format("Invalid BIN format: {}", bin)) {}
        };
}