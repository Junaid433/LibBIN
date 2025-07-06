#pragma once

namespace LibBIN {
    inline constexpr int version_major = 1;
    inline constexpr int version_minor = 0;
    inline constexpr int version_patch = 0;
    [[nodiscard]] consteval auto version_string() noexcept -> const char* {
        return "1.0.0";
    }
}
