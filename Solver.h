#ifndef HODGKIN_HUXLEY_MODEL_SOLVER_H
#define HODGKIN_HUXLEY_MODEL_SOLVER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Params.h"

class Solver {
private:
    std::vector<long double> V;
    std::vector<long double> N;
    std::vector<long double> M;
    std::vector<long double> H;

    std::fstream Vfile;
    std::fstream Nfile;
    std::fstream Mfile;
    std::fstream Hfile;
public:
    Solver();

    int init(const std::string &outputDir);

    void nextStep();

    void printValues();

    ~Solver();

private:
    void printVector(std::fstream &file, const std::vector<long double> &r);

    void loadValues(std::vector<long double> &dst, const std::vector<std::pair<long double, long double>> &src,
                    size_t N,
                    long double dx);

    long double approxValue(const std::pair<long double, long double> &p1,
                            const std::pair<long double, long double> &p2,
                            long double x);

    void nextStepN();

    void nextStepM();

    void nextStepH();

    void nextStepV();


    void printV();

    void printN();

    void printM();

    void printH();

    void tridiagonalMatrixAlgorithm(const std::vector<std::vector<long double> > &A, const std::vector<long double> &b,
                                    std::vector<long double> &res);
};


#endif //HODGKIN_HUXLEY_MODEL_SOLVER_H
