#pragma once

struct Connection {

    int idCity1;
    int idCity2;
    double distance;

    Connection(int city1, int city2, double d) 
    : idCity1(city1), idCity2(city2), distance(d) {}
};
