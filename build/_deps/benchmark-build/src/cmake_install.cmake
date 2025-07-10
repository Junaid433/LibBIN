# Install script for directory: /run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-src/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib" TYPE STATIC_LIBRARY FILES "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/src/libbenchmark.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib" TYPE STATIC_LIBRARY FILES "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/src/libbenchmark_main.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/include" TYPE DIRECTORY FILES
    "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-src/include/benchmark"
    "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/include/benchmark"
    FILES_MATCHING REGEX "/[^/]*\\.[^/]*h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib/cmake/benchmark" TYPE FILE FILES
    "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/benchmarkConfig.cmake"
    "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/benchmarkConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib/pkgconfig" TYPE FILE FILES "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/benchmark.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/usr/lib/cmake/benchmark/benchmarkTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/usr/lib/cmake/benchmark/benchmarkTargets.cmake"
         "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/src/CMakeFiles/Export/b256a20f0a266dda754aeb3bf48d4f58/benchmarkTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/usr/lib/cmake/benchmark/benchmarkTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/usr/lib/cmake/benchmark/benchmarkTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib/cmake/benchmark" TYPE FILE FILES "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/src/CMakeFiles/Export/b256a20f0a266dda754aeb3bf48d4f58/benchmarkTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib/cmake/benchmark" TYPE FILE FILES "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/src/CMakeFiles/Export/b256a20f0a266dda754aeb3bf48d4f58/benchmarkTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/share/doc/benchmark" TYPE DIRECTORY FILES "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-src/docs/")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/run/media/junaid/512 GiB HDD/Programming Arena/C++/LibBIN/build/_deps/benchmark-build/src/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
