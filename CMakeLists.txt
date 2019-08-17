cmake_minimum_required(VERSION 3.13)
project(EmbeddedTDD)

set(CMAKE_CXX_STANDARD 17)

enable_language(C)
enable_language(CXX)

add_subdirectory(LedDriver)
add_subdirectory(LightScheduler)
add_subdirectory(tests)