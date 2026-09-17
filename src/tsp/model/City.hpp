#pragma once
#include <string>

/**
 * @brief Represents a city node with its geographical coordinates.
 */
struct City {

    /** Unique identifier for the city in the DB. */
    int id;

    /** Name of the city. */
    std::string name;

    /** Latitude coordinate in degrees. */
    double latitude;

    /** Latitude coordinate in degrees. */
    double longitude;

    City(int id, const std::string& name, double lat, double lon) 
    : id(id), name(name), latitude(lat), longitude(lon) {}

};
