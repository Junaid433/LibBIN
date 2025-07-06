#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>

#include "lookup.hpp"

enum class OutputFormat {
    Pretty,
    JSON,
    CSV
};

struct CLIOptions {
    std::string bin;
    std::string file_input;
    std::string output_file;
    OutputFormat format = OutputFormat::Pretty;
    bool color = true;
    bool quiet = false;
    std::ostream* out_stream = &std::cout;
    std::ofstream owned_ofstream;
};

void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " [options]\n"
              << "Options:\n"
              << "  --bin <BIN>           Lookup a single BIN\n"
              << "  --file <filename>     Lookup multiple BINs from file\n"
              << "  --output <filename>   Write output to file\n"
              << "  --format <type>       Output format: pretty, json, csv (default: pretty)\n"
              << "  --color               Enable colored output (default)\n"
              << "  --no-color            Disable colored output\n"
              << "  --quiet               Suppress stdout (useful with --output)\n"
              << "  --help                Show this help\n";
}

OutputFormat parse_format(const std::string& s) {
    if (s == "json") return OutputFormat::JSON;
    if (s == "csv") return OutputFormat::CSV;
    return OutputFormat::Pretty;
}

void format_output(const LibBIN::Result& result, const CLIOptions& opts) {
    std::ostream& out = *(opts.out_stream);

    switch (opts.format) {
        case OutputFormat::Pretty:
            out << (opts.color ? "\033[1;32m" : "")
                << result.summary()
                << (opts.color ? "\033[0m" : "") << "\n";
            break;
        case OutputFormat::JSON:
            out << "{ \"scheme\": \"" << result.scheme << "\", "
                << "\"type\": \"" << result.type << "\", "
                << "\"brand\": \"" << result.brand << "\", "
                << "\"bank\": \"" << result.bank << "\", "
                << "\"country\": \"" << result.country << "\" }\n";
            break;
        case OutputFormat::CSV:
            out << result.scheme << "," << result.type << ","
                << result.brand << "," << result.bank << "," << result.country << "\n";
            break;
    }

    out.flush();
}

int run_cli_mode(const CLIOptions& opts) {
    std::string input;
    while (true) {
        std::cout << "Enter BIN (or 'exit'): ";
        if (!std::getline(std::cin, input) || input == "exit")
            break;

        auto result = LibBIN::Lookup::Search(input);
        if (result) {
            format_output(*result, opts);
        } else {
            std::cerr << "Error: " << result.error().what() << "\n";
        }
    }
    return 0;
}

int run_batch_mode(CLIOptions& opts) {
    std::ifstream infile(opts.file_input);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open input file\n";
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        auto result = LibBIN::Lookup::Search(line);
        if (result) {
            if (!opts.quiet || !opts.output_file.empty())
                format_output(*result, opts);
        } else {
            std::cerr << "Error for " << line << ": " << result.error().what() << "\n";
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    CLIOptions opts;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--bin" && i + 1 < argc) {
            opts.bin = argv[++i];
        } else if (arg == "--file" && i + 1 < argc) {
            opts.file_input = argv[++i];
        } else if (arg == "--output" && i + 1 < argc) {
            opts.output_file = argv[++i];
        } else if (arg == "--format" && i + 1 < argc) {
            opts.format = parse_format(argv[++i]);
        } else if (arg == "--no-color") {
            opts.color = false;
        } else if (arg == "--color") {
            opts.color = true;
        } else if (arg == "--quiet") {
            opts.quiet = true;
        } else if (arg == "--help") {
            print_usage(argv[0]);
            return 0;
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            print_usage(argv[0]);
            return 1;
        }
    }

    if (!opts.output_file.empty()) {
        opts.owned_ofstream.open(opts.output_file);
        if (!opts.owned_ofstream.is_open()) {
            std::cerr << "Error: Failed to open output file\n";
            return 1;
        }
        opts.out_stream = &opts.owned_ofstream;
    }

    LibBIN::Lookup::load_bins();

    if (!opts.bin.empty()) {
        auto result = LibBIN::Lookup::Search(opts.bin);
        if (result) {
            if (!opts.quiet || !opts.output_file.empty())
                format_output(*result, opts);
        } else {
            std::cerr << "Error: " << result.error().what() << "\n";
            return 1;
        }
        return 0;
    }

    if (!opts.file_input.empty()) {
        return run_batch_mode(opts);
    }

    return run_cli_mode(opts);
}
