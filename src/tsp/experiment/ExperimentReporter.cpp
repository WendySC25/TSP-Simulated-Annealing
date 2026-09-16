#include "ExperimentReporter.hpp"
#include <iomanip>
#include <limits>

ExperimentReporter::ExperimentReporter(){}
ExperimentReporter::~ExperimentReporter(){}

std::string ExperimentReporter::csvField(const std::string &raw){

    std::string escaped;
    escaped.reserve(raw.size() + 2);
    escaped.push_back('"');
    for(char c : raw){
        if(c == '"') escaped.push_back('"');
        escaped.push_back(c);
    }
    escaped.push_back('"');
    return escaped;
}

std::string ExperimentReporter::joinPath(const std::vector<int> &path){

    std::ostringstream oss;
    for(size_t i = 0; i < path.size(); ++i){
      if(i) oss << ';';
      oss << path[i];
    }
    return oss.str();
}

void ExperimentReporter::generateReportCSV(const std::string &filepath, const std::vector<RunResult> &results){
    
    std::ofstream out(filepath);
    if(!out.is_open())
        throw std::runtime_error("Useless: " + filepath);

    out << std::setprecision(std::numeric_limits<double>::max_digits10);
        
    out << "label,seed,epsilonP,targetP,initialT,tempSample,"
    << "coolingFactor,epsilon,batch,maxAttempts,"
    << "initialCost,initialTemperature,finalCost,elapsedMs,timestamp,finalPath\n";
            
    for(const RunResult &r : results){
        const RunConfig &c = r.config;
        out << csvField(c.label) << ','
                << c.seed << ','
                << c.epsilonP << ','
                << c.targetP << ','
                << c.initialT << ','
                << c.tempSample << ','
                << c.coolingFactor << ','
                << c.epsilon << ','
                << c.batch << ','
                << c.maxAttempts << ','
                << r.initialCost << ','
                << r.initialTemperature << ','
                << r.finalCost << ','
                << r.elapsedMs << ','
                << csvField(r.timestamp) << ','
                << csvField(joinPath(r.finalPath)) << '\n';                                               
    }           
}