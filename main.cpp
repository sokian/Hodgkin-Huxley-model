#include <iostream>
#include "DataLoader.h"
#include "Solver.h"

using namespace std;

int main(int argc, char **argv) {

    std::string paramsFileName;
    if (argc == 1) {
        paramsFileName = "default.txt";
    } else {
        paramsFileName = argv[1];
    }
    std::string outputDir;
    if (argc <= 2) {
        outputDir = "output/";
    } else {
        outputDir = argv[2];
        outputDir += "/";
    }
    int res = DataLoader::load(paramsFileName);
    if (res != 0) {
        std::cerr << "Main : Problem with input params file" << std::endl;
        return 1;
    }

    Solver solver;
    if (solver.init(outputDir) != 0) {
        std::cerr << "Main : error while initing Solver" << std::endl;
        return 1;
    }
    for (int j = 0, i = 0; j < Params::Nt; ++j) {
        if (j % Params::Times == 0) {
            solver.printValues();
        }
        solver.nextStep();
    }

    return 0;
}