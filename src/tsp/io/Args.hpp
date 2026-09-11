#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

struct Args {
    std::string dbPath;
    std::string instancePath;

    int     seed = 9695;

    // Initial Temperature parameters
    double  targetP = 0.95;
    double  epsilonP = 0.00001;
    double  initialT = 8.0;
    int     tempSample = 5000;

    // Simulated Annealing
    int     batchSize = 5000;       
    int     maxAttempts = 150;
    double  coolingFactor = 0.97;
    double  epsilon = 0.00001;
};

enum class ArgOption {
    Db, 
    Instance, 
    Seed, 
    TargetP, 
    EpsilonP, 
    InitialT, 
    BatchSize,
    CoolingFactor, 
    Epsilon, 
    MaxAttempts, 
    Help, 
    Unknown, 
    Sample
};

std::optional<Args> parseArgs(int argc, char** argv) {
    Args opts;
    std::vector<std::string> args(argv + 1, argv + argc);

    static const std::unordered_map<std::string, ArgOption> argMap = {
        {"-db", ArgOption::Db},
        {"-instance", ArgOption::Instance},
        {"-seed", ArgOption::Seed},
        {"-targetP", ArgOption::TargetP},
        {"-epsilonP", ArgOption::EpsilonP},
        {"-initialT", ArgOption::InitialT},
        {"-batchSize", ArgOption::BatchSize},
        {"-coolingFactor", ArgOption::CoolingFactor},
        {"-epsilon", ArgOption::Epsilon},
        {"-maxAttempts", ArgOption::MaxAttempts},
        {"-tempSample", ArgOption::Sample},
        {"-h", ArgOption::Help},
        {"-help", ArgOption::Help}
    };

    auto next = [&](size_t& i) -> std::optional<std::string> {
        if (i + 1 >= args.size()) return std::nullopt;
        return args[++i];
    };

    for (size_t i = 0; i < args.size(); i++) {
        const std::string& a = args[i];
        
        auto it = argMap.find(a);
        ArgOption opt = (it != argMap.end()) ? it->second : ArgOption::Unknown;

        switch (opt) {
            case ArgOption::Db: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.dbPath = *v;
                break;
            }

            case ArgOption::Instance: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.instancePath = *v;
                break;
            }

            case ArgOption::Seed: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.seed = std::stoi(*v);
                break;
            }

            case ArgOption::TargetP: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.targetP = std::stod(*v);
                break;
            }

            case ArgOption::EpsilonP: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.epsilonP = std::stod(*v);
                break;
            }

            case ArgOption::InitialT: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.initialT = std::stod(*v);
                break;
            }

            case ArgOption::BatchSize: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.batchSize = std::stoi(*v);
                break;
            }

            case ArgOption::CoolingFactor: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.coolingFactor = std::stod(*v);
                break;
            }

            case ArgOption::Epsilon: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.epsilon = std::stod(*v);
                break;
            }

            case ArgOption::MaxAttempts: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.maxAttempts = std::stoi(*v);
                break;
            }

            case ArgOption::Sample: {
                auto v = next(i); if (!v) return std::nullopt;
                opts.tempSample = std::stoi(*v);
                break;
            }

            case ArgOption::Help: {
                return std::nullopt;
            }

            case ArgOption::Unknown:

            default: {
                std::cerr << "Oh no: " << a << "\n";
                return std::nullopt;
            }
        }
    }

    if (opts.dbPath.empty() || opts.instancePath.empty()) {
        std::cerr << "Missing -db -instance\n";
        return std::nullopt;
    }
    
    return opts;
}