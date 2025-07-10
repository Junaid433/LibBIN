# CMake generated Testfile for 
# Source directory: /run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN
# Build directory: /run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/run_tests[1]_include.cmake")
add_test(Benchmark "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/run_benchmark")
set_tests_properties(Benchmark PROPERTIES  _BACKTRACE_TRIPLES "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/CMakeLists.txt;76;add_test;/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
subdirs("_deps/benchmark-build")
