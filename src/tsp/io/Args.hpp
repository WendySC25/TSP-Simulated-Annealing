#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

/**
 * @brief Configuration parameters for the Simulated Annealing execution.
 */
struct Args {
    /** Path to the SQLite database. */
    std::string dbPath;
    
    /** Path to the problem instance file. */
    std::string instancePath;

    /** Random Number Generator (RNG) seed. */
    int seed = 9695;

    // Initial Temperature parameters

    /** Target acceptance probability for initial temperature. */
    double targetP = 0.95;
    
    /** Tolerance for the initial temperature search. */
    double epsilonP = 0.00001;
    
    /** Starting temperature. */
    double initialT = 8.0;
    
    /** Sample size for temperature initialization. */
    int tempSample = 5000;

    // Simulated Annealing

    /** Number of iterations per temperature level. */
    int batchSize = 5000;       
    
    /** Maximum temperature drops without improvement. */
    int maxAttempts = 150;
    
    /** Multiplier for cooling the temperature (alpha). */
    double coolingFactor = 0.97;
    
    /** Minimum temperature threshold to stop execution. */
    double epsilon = 0.00001;
};

/**
 * @brief Identifiers for supported command-line flags.
 */
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

/**
 * @brief Parses command-line arguments and maps them into an Args structure.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return An std::optional containing the parsed Args, or std::nullopt on failure/help request.
 */
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