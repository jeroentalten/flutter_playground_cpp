# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(flutter_playground_cpp_library VERSION 0.0.1 LANGUAGES C CXX)

add_library(flutter_playground_cpp SHARED
  "flutter_playground_cpp.cpp"
  "flutter_playground_cpp.h"
  "httplib.h"
)

set_target_properties(flutter_playground_cpp PROPERTIES
  CXX_STANDARD 20  # Set C++14 or adjust according to your needs
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  PUBLIC_HEADER flutter_playground_cpp.h
  OUTPUT_NAME "flutter_playground_cpp"
)

target_compile_definitions(flutter_playground_cpp PUBLIC DART_SHARED_LIB)

find_package(OpenSSL REQUIRED)

# If you need to link any specific C++ libraries (standard or others), do it here
# For example, linking the C++ standard library (this may not be needed in most cases):
target_link_libraries(flutter_playground_cpp PRIVATE
  ${CMAKE_DL_LIBS} # Add other libraries if necessary
  OpenSSL::SSL
  OpenSSL::Crypto
)

# If you have other include directories, specify them
target_include_directories(flutter_playground_cpp PRIVATE
  ${CMAKE_SOURCE_DIR}/include  # Add any necessary include directories
)
