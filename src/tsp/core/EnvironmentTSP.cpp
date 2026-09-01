#include "EnvironmentTSP.hpp"

EnvironmentTSP::EnvironmentTSP(const std::vector<City>& cities, const std::vector<Connection>& connetions) : n (cities.size()){
    n = cities.size();
    matrix.assign(n, std::vector<double>(n, -1.0));
    
    std::vector<double> distances;
    distances.reserve(connetions.size());

    for (int i = 0; i < n; ++i) {
        matrix[i][i] = 0.0;
        idToIndex[cities[i].id] = i;
    }

    maxDS = -1e9;

    for (const Connection &conn : connetions) {
        auto it1 = idToIndex.find(conn.idCity1);
        auto it2 = idToIndex.find(conn.idCity2);
                
        if (it1 != idToIndex.end() && it2 != idToIndex.end()) {
            int u = it1->second;
            int v = it2->second;
                    
            if (matrix[u][v] < 0.0) {
                matrix[u][v] = conn.distance;
                matrix[v][u] = conn.distance;

                distances.push_back(conn.distance);

                if (conn.distance > maxDS) maxDS = conn.distance;       
            }      
        }
    }

    if(maxDS == -1e9) maxDS = R;

    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] < 0.0) {
                double dist = getNaturalDistance(cities[i].latitude, cities[i].longitude, cities[j].latitude, cities[j].longitude);
                matrix[i][j] = dist * maxDS;
            }
        }
    }

    std::sort(distances.begin(), distances.end(), std::greater<double>());
    normalizer = 0.0;
    int edges = std::min(n - 1, static_cast<int>(distances.size()));

    for (int i = 0; i < edges; ++i) 
        normalizer += distances[i];
    
    
    if (normalizer == 0.0) 
        normalizer = 1.0; 

}

EnvironmentTSP::~EnvironmentTSP(){}

const std::vector<std::vector<double> > &EnvironmentTSP::getMatrix() const{
    return matrix;
}

double EnvironmentTSP::getNormalizer() const{
    return normalizer;
}

double EnvironmentTSP::getMaxDS() const{
    return maxDS;
}