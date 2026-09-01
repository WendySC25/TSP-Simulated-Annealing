#pragma once
#include <vector>
#include <unordered_map>
#include "../utils/Haversine.hpp"
#include "../model/City.hpp"
#include "../model/Connection.hpp"

class EnviromentTSP{
    private:
        int n;
        double maxDS;
        double normalizer;
        std::vector<std::vector<double> > matrix;
        std::unordered_map<int, int> idToIndex;

    public:
        EnviromentTSP(const std::vector<City>& cities, const std::vector<Connection>& connetions);
        ~EnviromentTSP();
        const std::vector<std::vector<double> > &getMatrix() const;
        double getMaxDS() const;
        double getNormalizer() const;
            
};