# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(flutter_playground_cpp_library VERSION 0.0.1 LANGUAGES C)

add_library(flutter_playground_cpp SHARED
  "flutter_playground_cpp.c"
)

set_target_properties(flutter_playground_cpp PROPERTIES
  PUBLIC_HEADER flutter_playground_cpp.h
  OUTPUT_NAME "flutter_playground_cpp"
)

target_compile_definitions(flutter_playground_cpp PUBLIC DART_SHARED_LIB)
