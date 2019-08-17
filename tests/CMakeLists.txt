# include project source
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/tests/lights)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_library(LightsFakeTime ./lights/fake_time.cpp)

add_executable(RunAllTests
        lights/light_scheduler_test.cpp
        lights/fake_time_test.cpp
        lights/LightController.cpp
        LedDriver/led_driver_test.cpp)

target_link_libraries(RunAllTests ${GTEST_BOTH_LIBRARIES} pthread LedDriver
        Lights LightsFakeTime)
