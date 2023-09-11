# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/jolluemil/Desktop/cpptasks/search_engine/cmake-build-release/_deps/json-src"
  "/Users/jolluemil/Desktop/cpptasks/search_engine/cmake-build-release/_deps/json-build"
  "/Users/jolluemil/Desktop/Cpptasks/search_engine/cmake-build-release/_deps/json-subbuild/json-populate-prefix"
  "/Users/jolluemil/Desktop/Cpptasks/search_engine/cmake-build-release/_deps/json-subbuild/json-populate-prefix/tmp"
  "/Users/jolluemil/Desktop/Cpptasks/search_engine/cmake-build-release/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
  "/Users/jolluemil/Desktop/Cpptasks/search_engine/cmake-build-release/_deps/json-subbuild/json-populate-prefix/src"
  "/Users/jolluemil/Desktop/Cpptasks/search_engine/cmake-build-release/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/jolluemil/Desktop/Cpptasks/search_engine/cmake-build-release/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp/${subDir}")
endforeach()
