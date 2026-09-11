#pragma once
#include "RunConfig.hpp"

struct RunResult {
    RunConfig   config;
    std::vector<int> finalPath;   
    std::string timestamp;   

    double    initialCost        = 0.0;   
    double    initialTemperature = 0.0;
    double    finalCost          = 0.0;
    long long elapsedMs          = 0;
};