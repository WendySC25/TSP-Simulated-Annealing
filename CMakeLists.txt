cmake_minimum_required(VERSION 3.14)
project(tsp-simulated-annealing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE SQLite::SQLite3)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(hello_test src/test/hello_test.cpp)
target_link_libraries(hello_test PRIVATE GTest::gtest_main SQLite::SQLite3)
target_include_directories(hello_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(hello_test)



