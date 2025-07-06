#include <iostream>
#include "lookup.hpp"

int main() {
    LibBIN::Lookup::load_bins();

    std::string bin;
    std::cout << "Enter BIN to lookup: ";
    std::cin >> bin;

    auto result = LibBIN::Lookup::Search(bin);
    if (result) {
        std::cout << "Lookup success:\n" << result->summary() << '\n';
    } else {
        std::cerr << "Lookup failed: " << result.error().what() << '\n';
        return 1;
    }

    return 0;
}
