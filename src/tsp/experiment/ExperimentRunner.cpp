#include "ExperimentRunner.hpp"

std::string ExperimentRunner::nowTimestamp(){
    auto noww = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(noww);
    std::tm tmBuf;
    #if defined(_WIN32)
        localtime_s(&tmBuf, &t);
    #else
        localtime_r(&t, &tmBuf);
    #endif
    std::ostringstream oss;
    oss << std::put_time(&tmBuf, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}

ExperimentRunner::ExperimentRunner(const std::vector<std::vector<double> > &matrix, double normalizer, int numThreads)
: matrix(matrix), normalizer(normalizer), numThreads(numThreads > 0 ? numThreads : std::max(1u, std::thread::hardware_concurrency())) {}

RunResult ExperimentRunner::runOne(const RunConfig &cfg){
    auto start = std::chrono::steady_clock::now();
    
    RunResult result;
    result.config = cfg;
    result.timestamp = nowTimestamp();

    SolutionTSP s(matrix, normalizer, cfg.seed);
    result.initialCost = s.getCost();

    InitialTemperature initTemp(cfg.epsilonP, cfg.targetP, cfg.initialT, cfg.tempSample);
    double T = initTemp.computeInitialT(s);
    result.initialTemperature = T;
    
    SimulatedAnnealing sa(cfg.coolingFactor, cfg.epsilon, cfg.batch, cfg.maxAttempts);
    sa.run(T, s);
    result.finalCost = s.getCost();
    result.finalPath = s.getPath();

    auto end = std::chrono::steady_clock::now();
    result.elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    return result;
}

void ExperimentRunner::worker(const std::vector<RunConfig> &configs, std::vector<RunResult> &results, size_t begin, size_t end, std::atomic<int>& completed){
    for(size_t i = begin; i<end; i++){
        results[i] = runOne(configs[i]);
        completed++;
    }
}

std::vector<RunResult> ExperimentRunner::run(const std::vector<RunConfig> &configs) {
    std::vector<RunResult> results(configs.size());
    if(configs.empty()) return results;

    std::atomic<int> completed(0);

    int threadsToUse = std::min<int>(numThreads, static_cast<int>(configs.size()));
    
    std::vector<std::thread> pool;
    pool.reserve(threadsToUse);
    
    size_t total = configs.size();
    size_t chunk = (total + threadsToUse - 1) / threadsToUse;
    
    for(unsigned int t = 0; t < threadsToUse; t++){
        size_t begin = t * chunk;
        size_t end = std::min(total, begin + chunk);
        if(begin >= end) 
            break;
        pool.emplace_back(&ExperimentRunner::worker, this, std::cref(configs), std::ref(results), begin, end, std::ref(completed));
    }

    
    while (completed < configs.size()) {
        std::cout << "\rCompleted: " << completed.load() << " / " << configs.size();
        std::cout.flush(); 
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::cout << "\rExperiments completed: " << configs.size() << " / " << configs.size() << "\n\n";
    
    for(auto &th : pool) th.join();
    return results;
}

std::vector<RunConfig> ExperimentRunner::assignSeeds(int numSeeds, const RunConfig &baseCofig){
    
    std::vector<RunConfig> configs;
    configs.reserve(numSeeds);
    
    for(int i = 0; i < numSeeds; i++) {
        RunConfig cfg = baseCofig;
        cfg.seed = i + cfg.seed;
        configs.push_back(cfg);
    }
    
    return configs;
}

std::vector<RunConfig> ExperimentRunner::generateRandomConfigs(int numExperiments, const RunConfig &baseConfig) {
    std::vector<RunConfig> configs;
    configs.reserve(numExperiments);

    std::random_device rd;
    std::mt19937 gen(rd()); 

    std::uniform_int_distribution<int> distTargetP(7000, 9500); // 0.7000 a 0.9500
    std::uniform_int_distribution<int> distCooling(8500, 9800); // 0.8500 a 0.9800
    std::uniform_int_distribution<int> distBatch(1000, 5000);
    std::uniform_int_distribution<int> distTempSample(1000, 5000);
    std::uniform_int_distribution<int> distMaxAttempts(50, 200);

    for (int i = 0; i < numExperiments; i++) {
        RunConfig cfg = baseConfig;
        cfg.seed = baseConfig.seed + i; 
        cfg.targetP = distTargetP(gen) / 10000.0;
        cfg.coolingFactor = distCooling(gen) / 10000.0;
        cfg.batch = distBatch(gen);
        cfg.tempSample = distTempSample(gen);
        cfg.maxAttempts = distMaxAttempts(gen);

        cfg.label = "random_" + std::to_string(i);
        
        configs.push_back(cfg);
    }
    
    return configs;
}