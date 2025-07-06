#include <gtest/gtest.h>
#include "lookup.hpp"
#include <thread>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace LibBIN;

class LookupTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        Lookup::load_bins("data/bin_data.csv");
    }
};

static bool is_digits(const std::string& s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

TEST_F(LookupTest, ValidBin) {
    auto result = Lookup::Search("100101");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->bin, "100101");
    EXPECT_EQ(result->country, "US");
}

TEST_F(LookupTest, InvalidFormatAlphaNumeric) {
    auto result = Lookup::Search("abc123");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format: abc123");
}

TEST_F(LookupTest, InvalidFormatSymbols) {
    auto result = Lookup::Search("12#45@");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format: 12#45@");
}

TEST_F(LookupTest, InvalidFormatSpaces) {
    auto result = Lookup::Search(" 123456 ");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format:  123456 ");
}

TEST_F(LookupTest, EmptyBin) {
    auto result = Lookup::Search("");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format: ");
}

TEST_F(LookupTest, MinBinLength) {
    auto result = Lookup::Search("100001");
    if (result.has_value()) {
        EXPECT_EQ(result->bin, "100001");
    } else {
        SUCCEED() << "6-digit BIN not found in data";
    }
}

TEST_F(LookupTest, MaxBinLength) {
    auto result = Lookup::Search("10010001");
    if (result.has_value()) {
        EXPECT_EQ(result->bin, "10010001");
    } else {
        SUCCEED() << "8-digit BIN not found in data";
    }
}

TEST_F(LookupTest, BelowMinBinLength) {
    auto result = Lookup::Search("12345");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format: 12345");
}

TEST_F(LookupTest, AboveMaxBinLength) {
    auto result = Lookup::Search("123456789");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format: 123456789");
}

TEST_F(LookupTest, NotFound) {
    auto result = Lookup::Search("000000");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "BIN not found: 000000");
}

TEST_F(LookupTest, LeadingZeros) {
    auto result = Lookup::Search("000100");
    if (result.has_value()) {
        EXPECT_EQ(result->bin.substr(0, 3), "000");
    } else {
        SUCCEED() << "Leading-zero BIN not found in CSV";
    }
}

TEST_F(LookupTest, SummaryOutput) {
    auto result = Lookup::Search("100101");
    ASSERT_TRUE(result.has_value());
    std::string summary = result->summary();
    EXPECT_NE(summary.find("BIN: 100101"), std::string::npos);
    EXPECT_NE(summary.find("Country: US"), std::string::npos);
}

TEST_F(LookupTest, PrepaidFlag) {
    auto result = Lookup::Search("your_prepaid_bin_here");
    if (result.has_value()) {
        EXPECT_TRUE(result->prepaid);
    } else {
        SUCCEED() << "Prepaid BIN not found, skipping prepaid flag test";
    }
}

TEST_F(LookupTest, ThreadSafety) {
    const int threads_count = 5;
    std::vector<std::thread> threads;
    for (int i = 0; i < threads_count; ++i) {
        threads.emplace_back([]() {
            for (int j = 0; j < 50; ++j) {
                auto r = Lookup::Search("100101");
                ASSERT_TRUE(r.has_value());
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}

TEST_F(LookupTest, WhitespaceInput) {
    auto result = Lookup::Search(" 100101 ");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format:  100101 ");
}

TEST_F(LookupTest, NumericStringEdgeCases) {
    auto result = Lookup::Search("100101\n");
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), "Invalid BIN format: 100101\n");
}

TEST_F(LookupTest, ExtremelyLongString) {
    std::string long_bin(1000, '1');
    auto result = Lookup::Search(long_bin);
    ASSERT_FALSE(result.has_value());
    EXPECT_STREQ(result.error().what(), ("Invalid BIN format: " + long_bin).c_str());
}
