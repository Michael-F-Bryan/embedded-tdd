cmake_minimum_required(VERSION 3.13)
project(EmbeddedTDD)

enable_language(C)
enable_language(CXX)

add_subdirectory(LedDriver)
add_subdirectory(LightScheduler)
add_subdirectory(tests)