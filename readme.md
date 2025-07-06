
---

# LibBIN

**LibBIN** is a modern, blazing-fast C++23 library and CLI tool for **Bank Identification Number (BIN)** lookup.
Designed for performance-critical applications, LibBIN provides lightning-quick BIN data search directly from a local CSV database — outperforming basic Python BIN lookup APIs by orders of magnitude.

---

## ⚡ Why LibBIN?

* **Extremely fast:** Unlike typical Python BIN lookup APIs that rely on slow JSON parsing, network calls, or inefficient data structures, LibBIN uses optimized C++ data structures and algorithms to perform lookups in microseconds.
* **Local database:** No external API calls, no rate limits, no network latency — all BIN data resides locally for instant access.
* **Lightweight:** Minimal dependencies and compiled to efficient machine code for low memory usage and maximum throughput.
* **Production-ready:** Includes unit tests, benchmarks, and a clean API suitable for embedding in your backend, payment gateways, fraud detection systems, or CLI tools.

---

## 📁 Project Structure

```
LibBIN/
├── benchmarks/            # Performance tests using Google Benchmark
│   └── lookup_benchmark.cpp
├── data/                  # Local BIN CSV database (e.g. bin_data.csv)
│   └── bin_data.csv
├── examples/              # Practical usage examples
│   ├── basic_lookup.cpp   # Minimal CLI-like example
│   └── web_lookup.cpp     # Example for web server integration
├── include/               # Public headers
│   ├── libbin.hpp
│   ├── lookup.hpp
│   ├── result.hpp
│   ├── errors.hpp
│   └── version.hpp
├── src/                   # Core implementation
│   ├── lookup.cpp
│   └── result.cpp
├── tests/                 # Unit tests with GoogleTest
│   ├── test_main.cpp
│   └── test_lookup.cpp
├── CMakeLists.txt         # Build system
├── main.cpp               # CLI entry point with advanced interactive mode
└── scripts/               # Utility scripts (e.g. update_db.py)
```

---

## 🚀 Features

* Fast BIN lookup from local CSV database (milliseconds or faster)
* Interactive CLI with input validation, multi-query support, and file output
* Easy integration as a static C++ library in your projects
* Comprehensive unit tests with GoogleTest
* Performance benchmarks with Google Benchmark
* Extensible to different BIN data formats and outputs
* Examples demonstrating typical usage patterns (CLI, server)

---

## 🛠 Installation

### From Source

```bash
git clone https://github.com/Junaid433/LibBIN.git
cd LibBIN
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

This installs:

* CLI binary: `bin_lookup`
* Static library: `LibBIN`

---

## ⚙️ CLI Usage Examples

### 1. Interactive Mode (default)

Run without arguments to enter interactive prompt:

```bash
bin_lookup
```

Sample session:

```
Enter BIN (or 'exit'): 411111
BIN lookup successful:
Issuer: Visa
Country: United States
Type: Credit
...

Enter BIN (or 'exit'): exit
Goodbye!
```

---

### 2. Single BIN Lookup

Lookup a single BIN and print result:

```bash
bin_lookup --bin 411111
```

---

### 3. Batch Lookup from File

Lookup multiple BINs listed line-by-line in a file:

```bash
bin_lookup --file bins.txt
```

---

### 4. Output to File

Save output to a file instead of console:

```bash
bin_lookup --file bins.txt --output results.txt
```

---

### 5. Output Format Options

Choose output format: `pretty` (default), `json`, or `csv`.

```bash
bin_lookup --bin 411111 --format json
bin_lookup --file bins.txt --format csv --output results.csv
```

---

### 6. Colorized Output

Color output is enabled by default. Disable color with:

```bash
bin_lookup --bin 411111 --no-color
```

---

### 7. Quiet Mode

Suppress stdout output (useful with file output):

```bash
bin_lookup --file bins.txt --output results.txt --quiet
```

---

### 8. Help

Show usage info:

```bash
bin_lookup --help
```

---

### Example: Combined Usage

```bash
bin_lookup --file bins.txt --output results.json --format json --no-color --quiet
```

---

## 📚 Library Usage Example (C++)

Embed LibBIN in your C++ project by including the header and linking the static library:

```cpp
#include "lookup.hpp"
#include <iostream>

int main() {
    if (!LibBIN::Lookup::load_bins("data/bin_data.csv")) {
        std::cerr << "Failed to load BIN database\n";
        return 1;
    }

    auto result = LibBIN::Lookup::Search("411111");
    if (result) {
        std::cout << result->summary() << std::endl;
    } else {
        std::cerr << "BIN not found or error\n";
    }
    return 0;
}
```

See `examples/basic_lookup.cpp` for a runnable minimal example.

---

## 🐍 & 🌐 Python Integration and Web Server

### Using LibBIN from Python

* **Call CLI from Python:**

```python
import subprocess

def lookup_bin(bin_code: str) -> str:
    result = subprocess.run(["bin_lookup"], input=bin_code + "\n", text=True, capture_output=True)
    return result.stdout.strip()

print(lookup_bin("411111"))
```

* **Python Bindings via Pybind11 (advanced):**

Create a Python extension for direct API access (see `libbin_py.cpp` example in docs).

---

### Running the Web Server Example

Build and run the web server example (`examples/web_lookup.cpp`):

```bash
cmake --build . --target web_lookup
./web_lookup
```

Query with:

```bash
curl -X POST -d "bin=411111" http://localhost:8080/lookup
```

Sample JSON response:

```json
{
  "bin": "411111",
  "issuer": "Visa",
  "country": "United States",
  "type": "Credit"
}
```

---

## 📊 Performance Comparison

| Method                      | Average Lookup Time       | Notes                          |
| --------------------------- | ------------------------- | ------------------------------ |
| LibBIN (C++ local lookup)   | **\~10-100 microseconds** | Optimized binary search on CSV |
| Typical Python API (remote) | \~100+ milliseconds       | Network call + JSON parsing    |
| Python local CSV naive      | \~1-10 milliseconds       | Slower due to Python overhead  |

LibBIN’s speed enables real-time fraud detection and payment validation at scale without external dependencies.

---

## 🧪 Development & Testing

Run unit tests:

```bash
cd build
make run_tests
```

Run benchmarks:

```bash
make run_benchmark
```

---

## 🤝 Contributing

Contributions welcome! Please:

* Fork the repository
* Create feature branches
* Write tests for new features or bug fixes
* Follow existing coding style and C++23 standards
* Submit pull requests with clear descriptions

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 📬 Contact

* Telegram: [@fakehecker](https://t.me/fakehecker)
* Repository: [https://github.com/Junaid433/LibBIN](https://github.com/Junaid433/LibBIN)

---

Thank you for choosing **LibBIN** — fast, reliable, and ready for production BIN lookups!

---
