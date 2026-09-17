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

add_library(tsp_core
    src/tsp/db/CityDatabase.cpp
    src/tsp/core/EnvironmentTSP.cpp
    src/tsp/core/SolutionTSP.cpp
    src/tsp/heuristic/InitialTemperature.cpp
    src/tsp/heuristic/SimulatedAnnealing.cpp
    src/tsp/experiment/ExperimentRunner.cpp
    src/tsp/experiment/ExperimentReporter.cpp
    src/tsp/app/TSPApp.cpp
)
target_link_libraries(tsp_core PUBLIC SQLite::SQLite3)
target_include_directories(tsp_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(tsp_runner src/main.cpp)
target_link_libraries(tsp_runner PRIVATE tsp_core)

add_executable(testT 
    src/test/hello_test.cpp  
    src/test/testHarversine.cpp
    src/test/testSolution.cpp 
)
target_link_libraries(testT PRIVATE tsp_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(testT)



