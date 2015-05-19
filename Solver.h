#ifndef HODGKIN_HUXLEY_MODEL_SOLVER_H
#define HODGKIN_HUXLEY_MODEL_SOLVER_H

#include <string>
#include <vector>
#include <map>
#include "Params.h"

class Solver {
private:
    std::vector<long double> V;
    std::vector<long double> N;
    std::vector<long double> M;
    std::vector<long double> H;
public:
    Solver();
    void init();
    void nextStep();
    void printV(const std::string &filename);
    void printN(const std::string &filename);
    void printM(const std::string &filename);
    void printH(const std::string &filename);
private:
    void printVector(const std::string &filename, const std::vector<long double> &r);
    void loadValues(std::vector<long double> &dst, const std::vector<std::pair<long double, long double>> &src, size_t N,
                    long double dx);
    long double approxValue(const std::pair<long double, long double> &p1,
                            const std::pair<long double, long double> &p2,
                            long double x);
};


#endif //HODGKIN_HUXLEY_MODEL_SOLVER_H
