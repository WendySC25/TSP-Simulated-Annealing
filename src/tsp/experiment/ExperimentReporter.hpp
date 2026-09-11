#pragma once
#include <fstream>
#include <sstream>

#include "RunConfig.hpp"
#include "RunResult.hpp"

class ExperimentReporter {
    private:
        std::string csvField(const std::string &raw);

    public:
        ExperimentReporter();
        ~ExperimentReporter();
        void generateReportCSV(const std::string &filepath, const std::vector<RunResult> &results);
};
