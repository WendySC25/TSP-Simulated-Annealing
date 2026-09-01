#pragma once
#include <vector>
#include <unordered_map>
#include "../utils/Haversine.hpp"
#include "../model/City.hpp"
#include "../model/Connection.hpp"

class EnvironmentTSP{
    private:
        int n;
        double maxDS;
        double normalizer;
        std::vector<std::vector<double> > matrix;
        std::unordered_map<int, int> idToIndex;

    public:
        EnvironmentTSP(const std::vector<City>& cities, const std::vector<Connection>& connetions);
        ~EnvironmentTSP();
        const std::vector<std::vector<double> > &getMatrix() const;
        double getMaxDS() const;
        double getNormalizer() const;
            
};