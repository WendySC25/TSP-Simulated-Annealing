#include <gtest/gtest.h>
#include "../tsp/core/SolutionTSP.hpp"
#include "../tsp/db/CityDatabase.hpp"
#include "tsp/core/EnvironmentTSP.hpp"


TEST(SolutionTest, tsp40) {

    std::vector<int> ids = { 1, 2, 3, 4, 5, 6, 7, 75, 163, 164, 165, 168, 172, 244, 327, 329, 331, 332, 333, 489, 490, 491, 492, 493, 496, 652, 653, 654, 656, 657, 815, 816, 817, 820, 978, 979, 980, 981, 982, 984 };

    double normalizer = 181500915.920000017;
    double evaluation = 4037072.073965357;
    double maxD = 4970123.960000000; 

    std::string db_path = "/Users/wendysc/Desktop/E/Ciencias/Semestre7/HDCO/TSP-Simulated-Annealing/data/db/tsp.db";
    CityDatabase db(db_path);
    std::vector<City> cities = db.getCities(ids);
    std::vector<Connection> connections = db.getConnections(ids);

    EnvironmentTSP env(cities, connections);

    int n = ids.size();
    SolutionTSP s(ids, env.getMatrix(), env.getNormalizer(), 25);

    EXPECT_NEAR(maxD, env.getMaxDS(), 1e-9);
    EXPECT_NEAR(normalizer, env.getNormalizer(), 1e-9);
    EXPECT_NEAR(evaluation, s.getCost(), 1e-8); // Ahhhh, se queda justo aqui
}


TEST(SolutionTest, tsp150) {

    std::vector<int> ids = { 1,2,3,4,5,6,7,8,9,11,12,14,16,17,19,20,22,23,25,26,27,74,75,77,163,164,165,166,167,168,169,171,172,173,174,176,179,181,182,183,184,185,186,187,244,297,326,327,328,329,330,331,332,333,334,336,339,340,343,344,345,346,347,349,350,351,352,353,444,483,489,490,491,492,493,494,495,496,499,500,501,502,504,505,507,508,509,510,511,512,520,652,653,654,655,656,657,658,660,661,662,663,665,666,667,668,670,671,673,674,675,676,678,815,816,817,818,819,820,821,822,823,825,826,828,829,832,837,839,840,978,979,980,981,982,984,985,986,988,990,991,995,999,1001,1003,1004,1037,1038,1073,1075 };

    double normalizer = 722598785.020000100;
    double evaluation = 6092371.483582111; 
    double maxD = 4978506.480000000;

    std::string db_path = "/Users/wendysc/Desktop/E/Ciencias/Semestre7/HDCO/TSP-Simulated-Annealing/data/db/tsp.db";
    CityDatabase db(db_path);
    std::vector<City> cities = db.getCities(ids);
    std::vector<Connection> connections = db.getConnections(ids);

    EnvironmentTSP env(cities, connections);

    int n = ids.size();
    SolutionTSP s(ids, env.getMatrix(), env.getNormalizer(), 1);

    EXPECT_NEAR(maxD, env.getMaxDS(), 1e-9);
    EXPECT_NEAR(normalizer, env.getNormalizer(), 1e-9);
    EXPECT_NEAR(evaluation, s.getCost(), 1e-9);
}

