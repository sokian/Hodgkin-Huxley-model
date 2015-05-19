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
    int res = DataLoader::load(paramsFileName);
    if (res != 0) {
        std::cerr << "Main : Problem with input params file" << std::endl;
        return 1;
    }

    Solver solver;
    solver.init();
    for (int i = 0; i < Params::Nt; ++i) {
        solver.nextStep();
        solver.printV(std::string("V_") + std::to_string(i) + ".txt");
        solver.printN(std::string("N_") + std::to_string(i) + ".txt");
        solver.printM(std::string("M_") + std::to_string(i) + ".txt");
        solver.printH(std::string("H_") + std::to_string(i) + ".txt");
    }

    return 0;
}