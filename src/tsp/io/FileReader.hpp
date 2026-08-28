#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>

inline std::vector<int> readFile(std::string &filepath){

    std::ifstream file(filepath);

    if(!file.is_open()) 
        throw std::runtime_error("Useless path: " + filepath);
    
    std::vector<int> ids;
    std::string line;

    if(std::getline(file,line)){
        std::stringstream ss(line);
        std::string id;

        while(std::getline(ss,id,',')) 
            ids.push_back(std::stoi(id));
    }

    return ids;
}
