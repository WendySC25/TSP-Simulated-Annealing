#pragma once
#include <cmath>

/// @brief Pi constant for angular conversions.
const double PI = 3.14159265358979323846;

/// @brief Earth's mean radius in meters.
const double R = 6373000.0;

/**
 * @brief Converts an angle from degrees to radians.
 * 
 * @param degree The angle in degrees.
 * @return The corresponding angle in radians.
 */
inline double toRad(double degree){
    return (degree * PI) / 180.0;
}

/**
 * @brief Calculates the great-circle distance between two geographic coordinates using the Haversine formula.
 * 
 * @param latA Latitude of the first point in degrees.
 * @param lonA Longitude of the first point in degrees.
 * @param latB Latitude of the second point in degrees.
 * @param lonB Longitude of the second point in degrees.
 * @return The distance between the two points in meters.
 */
inline double getNaturalDistance(double latA, double lonA, double latB, double lonB) {
    
    double latA_rad = toRad(latA);
    double lonA_rad = toRad(lonA);
    double latB_rad = toRad(latB);
    double lonB_rad = toRad(lonB);

    double A = std::pow(std::sin((latB_rad - latA_rad)/2.0),2) +
               std::cos(latA_rad) * std::cos(latB_rad) *
               std::pow(std::sin((lonB_rad - lonA_rad)/2.0),2);
            
    double C = 2.0 * std::atan2(std::sqrt(A), std::sqrt(1.0 - A));
    return R * C;
}
