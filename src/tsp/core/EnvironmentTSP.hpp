#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "../utils/Haversine.hpp"
#include "../model/City.hpp"
#include "../model/Connection.hpp"

/**
 * @brief Manages the TSP environment, including distances and ID mappings.
 */
class EnvironmentTSP{
    private:
        /** Number of cities in the environment. */
        int n;
        
        /** Maximum distance found in the environment. */
        double maxDS;
        
        /** Value used to normalize distances. */
        double normalizer;
        
        /** 2D matrix storing distances between all pairs of cities. */
        std::vector<std::vector<double> > matrix;

        /** Maps a real city ID to its internal 0-indexed matrix position. */
        std::unordered_map<int, int> idToIndex;
        
        /** Maps an internal matrix index back to its real city ID. */
        std::vector<int> indexToId;
        
        /** Reference to the list of cities. */
        std::vector<City>& indexCities;

    public:
        EnvironmentTSP(const std::vector<City>& cities, const std::vector<Connection>& connetions);
        ~EnvironmentTSP();

        /**
         * @brief Gets the full distance matrix with the cost funtion.
         * @return A constant reference to the 2D distance matrix.
         */
        const std::vector<std::vector<double> > &getMatrix() const;

        /**
         * @brief Gets the maximum recorded distance.
         * @return The maximum distance value.
         */
        double getMaxDS() const;

        /**
         * @brief Gets the distance normalization factor.
         * @return The normalization factor.
         */
        double getNormalizer() const;

        /**
         * @brief Converts a path of internal indices to a path of real city IDs.
         * 
         * @param path The sequence of internal indices.
         * @return The sequence of actual city identifiers.
         */
        std::vector<int> getPathIds(const std::vector<int>& path) const;

        /**
         * @brief Retrieves the geographic coordinates for a given route.
         * 
         * @param path The sequence of internal indices.
         * @return A list of (latitude, longitude) pairs representing the route.
         */
        std::vector<std::pair<double, double> > getPathCoords(const std::vector<int>& path) const;
        
};