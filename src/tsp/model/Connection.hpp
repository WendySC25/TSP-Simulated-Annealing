#pragma once

/**
 * @brief Represents a path or edge between two cities.
 */
struct Connection {

    /** Identifier for the first city. */
    int idCity1;

    /** Identifier for the second city. */
    int idCity2;

    /** Distance between the two cities. */
    double distance;

    Connection(int city1, int city2, double d) 
    : idCity1(city1), idCity2(city2), distance(d) {}
};
