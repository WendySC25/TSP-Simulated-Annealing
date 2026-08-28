#pragma once
#include <string>

struct City {

    int         id;
    std::string name;
    double      latitude;
    double      longitude;

    City(int id, const std::string& name, double lat, double lon) 
    : id(id), name(name), latitude(lat), longitude(lon) {}

};
