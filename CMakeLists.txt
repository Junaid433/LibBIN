cmake_minimum_required(VERSION 3.16)
project(LibBIN VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "")
set(CMAKE_C_FLAGS "")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/lookup.cpp
    src/result.cpp
)

add_library(BIN STATIC ${SOURCES})
target_include_directories(BIN PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(bin_lookup
    main.cpp
    src/lookup.cpp
    src/result.cpp
)
target_link_libraries(bin_lookup PRIVATE pthread)
target_include_directories(bin_lookup PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests
    tests/test_main.cpp
    tests/test_lookup.cpp
)

add_custom_command(
    TARGET run_tests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${CMAKE_BINARY_DIR}/data"
)

add_custom_command(
    TARGET run_tests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/data/bin_data.csv"
        "${CMAKE_BINARY_DIR}/data/bin_data.csv"
)

target_link_libraries(run_tests PRIVATE BIN gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(run_tests)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.7.1
)
FetchContent_MakeAvailable(benchmark)

add_executable(run_benchmark
    benchmarks/lookup_benchmark.cpp
    src/lookup.cpp
    src/result.cpp
)

target_link_libraries(run_benchmark PRIVATE benchmark pthread)
target_include_directories(run_benchmark PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_test(NAME Benchmark COMMAND run_benchmark)

install(TARGETS BIN run_tests run_benchmark bin_lookup
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES "${CMAKE_SOURCE_DIR}/data/bin_data.csv"
        DESTINATION /usr/share/LibBIN)
