#pragma once
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <iostream>

#include "RunConfig.hpp"
#include "RunResult.hpp"

/**
 * @brief Handles the exportation of experiment results to external file formats.
 */
class ExperimentReporter {
    private:
        /**
         * @brief Escapes and formats a string to be safely inserted into a CSV cell.
         * @param raw The raw string.
         * @return The CSV-safe string.
         */
        std::string csvField(const std::string &raw);

        /**
         * @brief Converts a route path into a single delimited string.
         * @param path The sequence of node identifiers.
         * @return A string representation of the path.
         */
        std::string joinPath(const std::vector<int> &path);

    public:
        ExperimentReporter();
        ~ExperimentReporter();
        
        /**
         * @brief Generates a CSV file containing the metrics of all executed experiments.
         * 
         * @param filepath The destination path for the CSV file.
         * @param results The list of results to export.
         */
        void generateReportCSV(const std::string &filepath, const std::vector<RunResult> &results);

        /**
         * @brief Generates a .tsp file containing the sequence of City IDs for the best route.
         * @param filepath The destination path.
         * @param path The translated sequence of real City IDs.
         */
        void generateSolutionFile(const std::string &filepath, const std::vector<int> &path);

        /**
         * @brief Generates a .coords file containing the longitude and latitude of the best route.
         * @param filepath The destination path.
         * @param coords Vector of (longitude, latitude) pairs.
         */
        void generateCoordsFile(const std::string &filepath, const std::vector<std::pair<double, double> > &coords);
};
