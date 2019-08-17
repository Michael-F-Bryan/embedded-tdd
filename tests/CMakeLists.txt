# include project source
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/LedDriver)
include_directories(${PROJECT_SOURCE_DIR}/include/LightScheduler)
include_directories(${PROJECT_SOURCE_DIR}/tests/LightScheduler)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_library(LightSchedulerFakeTime ./LightScheduler/fake_time.cpp)

add_executable(RunAllTests
        LightScheduler/light_scheduler_test.cpp
        LedDriver/led_driver_test.cpp)

target_link_libraries(RunAllTests ${GTEST_BOTH_LIBRARIES} pthread LedDriver
        LightScheduler LightSchedulerFakeTime)
