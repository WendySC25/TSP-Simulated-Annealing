#include <gtest/gtest.h>
#include "../tsp/utils/Haversine.hpp"

/*
Degrees to Rad
*/
TEST(HaversineTest, DegreeToRad) {
    EXPECT_DOUBLE_EQ(toRad(0.0), 0.0);
    EXPECT_NEAR(toRad(180.0), PI, 1e-9);
    EXPECT_NEAR(toRad(90.0), PI / 2.0, 1e-9);
}

/*
Dis = 0
*/
TEST(HaversineTest, DistZero) {
    double lat = 19.4326;
    double lon = -99.1332;
    double dist = getNaturalDistance(lat, lon, lat, lon);
    EXPECT_NEAR(dist, 0.0, 1e-9);
}

/*
Antipodal
*/
TEST(HaversineTest, DistOpposite) {
    double dE = PI * R;
    double dC = getNaturalDistance(0.0, 0.0, 0.0, 180.0);
    
    EXPECT_NEAR(dC, dE, 1e-4);
}

/*
Simetric
*/
TEST(HaversineTest, SimetricDist) {
    double distAB = getNaturalDistance(19.43, -99.13, 40.71, -74.00);
    double distBA = getNaturalDistance(40.71, -74.00, 19.43, -99.13);
    
    EXPECT_DOUBLE_EQ(distAB, distBA);
}