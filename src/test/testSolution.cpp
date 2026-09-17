#include <gtest/gtest.h>
#include "../tsp/core/SolutionTSP.hpp"
#include "../tsp/db/CityDatabase.hpp"
#include "tsp/core/EnvironmentTSP.hpp"

namespace {
    std::vector<std::vector<double> > fixedMatrix(){
        return {
            {0,  10, 20, 30},
            {10, 0,  15, 25},
            {20, 15, 0,  5 },
            {30, 25, 5,  0 }
        };
    }

}

TEST(SolutionTest, tsp40) {

    std::vector<int> ids = { 1, 2, 3, 4, 5, 6, 7, 75, 163, 164, 165, 168, 172, 244, 327, 329, 331, 332, 333, 489, 490, 491, 492, 493, 496, 652, 653, 654, 656, 657, 815, 816, 817, 820, 978, 979, 980, 981, 982, 984 };

    double normalizer = 181500915.901503116;
    double evaluation = 4037072.076285812;
    double maxD = 4970123.962350251; 

    std::string db_path = "../data/db/tsp.sql";
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

    double normalizer = 722598784.973402858;
    double evaluation = 6092371.482090380; 
    double maxD = 4978506.478459956;

    std::string db_path = "../data/db/tsp.sql";
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

TEST(SolutionTSP, SimplePathEvaluaction){
    auto m = fixedMatrix();
    double normalizer = 100.0;
    std::vector<int> ids = {0,1,2,3};
    
    SolutionTSP s(ids, m, normalizer, 0);
    double expected = (10.0 + 15.0 + 5.0) / normalizer;
    EXPECT_NEAR(s.getCost(), expected, 1e-9);
}

TEST(SolutionTSP, GetSwapCostSameIndexReturnsCurrentCost){
    auto m = fixedMatrix();
    std::vector<int> ids = {0,1,2,3};
    SolutionTSP s(ids, m, 100.0, 0);
    double before = s.getCost();
    EXPECT_DOUBLE_EQ(s.getSwapCost(2,2), before);
}

TEST(SolutionTSP, GetSwapCostPredictsCostOfSwappedPath){
    auto m = fixedMatrix();
    double normalizer = 100.0;
    std::vector<int> ids = {0,1,2,3};
    SolutionTSP s(ids, m, normalizer, 0);

    double predicted = s.getSwapCost(1,3);
    EXPECT_NEAR(predicted, 0.5, 1e-9);
}

TEST(SolutionTSP, GetSwapCostAdjacentIndices){
    auto m = fixedMatrix();
    double normalizer = 100.0;
    std::vector<int> ids = {0,1,2,3};
    SolutionTSP s(ids, m, normalizer, 0);

    double predicted = s.getSwapCost(1,2);
    EXPECT_NEAR(predicted, 0.6, 1e-9);
}

TEST(SolutionTSP, AcceptProposeUpdatesPathAndCostConsistently){
    auto m = fixedMatrix();
    double normalizer = 100.0;
    std::vector<int> ids = {0,1,2,3};
    SolutionTSP s(ids, m, normalizer, 7);

    auto pathBefore = s.getPath();
    double predicted = s.proposeNeightborhCost();
    s.acceptPropose();

    EXPECT_NE(s.getPath(), pathBefore);
    EXPECT_NEAR(s.getCost(), predicted, 1e-9);

    double recomputed = s.evaluate();
    EXPECT_NEAR(recomputed, predicted, 1e-9);
}

TEST(SolutionTSP, SaveBestAndRestoreBestRoundTrip){
    auto m = fixedMatrix();
    std::vector<int> ids = {0,1,2,3};
    SolutionTSP s(ids, m, 100.0, 7);

    double originalCost = s.getCost();
    auto originalPath = s.getPath();
    s.saveBest();

    s.proposeNeightborhCost();
    s.acceptPropose();

    EXPECT_NE(s.getPath(), originalPath);

    s.restoreBest();
    EXPECT_EQ(s.getPath(), originalPath);
    EXPECT_NEAR(s.getCost(), originalCost, 1e-9);
}

TEST(SolutionTSP, ToStringContainsAllPathIndices){
    auto m = fixedMatrix();
    std::vector<int> ids = {0,1,2,3};
    SolutionTSP s(ids, m, 100.0, 0);
    std::string str = s.toString();
    for(int i = 0; i < 4; ++i)
        EXPECT_NE(str.find(std::to_string(i)), std::string::npos);
}

TEST(SolutionTSP, IsFactibleMatchesBookDefinition){
    auto m = fixedMatrix();
    std::vector<int> ids = {0,1,2,3};
    double normalizer = 100.0;
    SolutionTSP s(ids, m, normalizer, 0);
    EXPECT_TRUE(s.isFactible());
}

TEST(SolutionTSP, RestoreBestBeforeAnySaveDoesNotCorruptSolution){
    auto m = fixedMatrix();
    std::vector<int> ids = {0,1,2,3};
    SolutionTSP s(ids, m, 100.0, 0);

    double costBefore = s.getCost();
    auto pathBefore = s.getPath();

    s.restoreBest();

    EXPECT_EQ(s.getPath().size(), pathBefore.size()) << "restoreBest() witjout saveBest()";
}

TEST(SolutionTSP, RandomConstructorProducesValidPermutation){
    auto m = fixedMatrix();
    SolutionTSP s(m, 100.0, 42);
    auto path = s.getPath();
    std::vector<int> sorted = path;
    std::sort(sorted.begin(), sorted.end());
    for(size_t i = 0; i < sorted.size(); ++i)
        EXPECT_EQ(sorted[i], static_cast<int>(i));
}


