#include <iostream>
#include "tsp/io/Args.hpp"
#include "tsp/app/TSPApp.hpp"

using namespace std;

int main(int argc, char** argv) {
    try {
        auto optsOpt = parseArgs(argc, argv);

        if (!optsOpt) {
            std::cerr << "Usage: ./tsp_runner -db <path> -instance <path> [-mode single|random|seeds] [-nRuns N] [-out path] ... Read README\n\n";
            return 1;
        }
        const Args options = optsOpt.value();
        
        TSPApp app;
        return app.run(options);

    } catch (const std::exception& e) {
        std::cerr << "Fatal Error :c " << e.what() << '\n';
        return 1;
    }
    return 0;
}