#include "Solver.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>

Solver::Solver() {
}

void Solver::init() {
    loadValues(V, Params::V, Params::Nx, Params::dx);
    loadValues(N, Params::N, Params::Nx, Params::dx);
    loadValues(M, Params::M, Params::Nx, Params::dx);
    loadValues(H, Params::H, Params::Nx, Params::dx);
}

void Solver::printV(const std::string &filename) {
    printVector(filename, V);
}

void Solver::printN(const std::string &filename) {
    printVector(filename, N);
}

void Solver::printM(const std::string &filename) {
    printVector(filename, M);
}

void Solver::printH(const std::string &filename) {
    printVector(filename, H);
}

void Solver::printVector(const std::string &filename, const std::vector<long double> &r) {
    std::fstream file;
    file.open(filename, std::ios_base::in);
    if (!file.is_open()) {
        std::cerr << "Error while open file for writing: " << filename << std::endl;
        return;
    }
    for (size_t i = 0; i < r.size(); ++i) {
        long double x = i * Params::dx;
        long double y = r[i];
        file << x << " " << y << "\n";
    }
    file.close();
}

void Solver::loadValues(std::vector<long double> &dst, const std::vector<std::pair<long double, long double> > &src,
                        size_t N, long double dx) {
    dst.assign(N + 1, 0.0);
    std::vector<std::pair<long double, long double> > S = src;
    for (std::pair<long double, long double> &p : S) {
        p.first = p.first / 100.0 * Params::LEN;
    }
    std::sort(S.begin(), S.end());
    assert(S.size() >= 2);

    for (int i = 0; i <= N; ++i) {
        long double x = dx * i;
        std::vector<std::pair<long double, long double> >::iterator it1;
        std::vector<std::pair<long double, long double> >::iterator it2;
        it1 = std::lower_bound(S.begin(), S.end(), std::make_pair(x, (long double)0.0));
        if (it1 == S.end()) {
            --it1;
        }
        it2 = it1;
        --it1;
        dst[i] = approxValue(*it1, *it2, x);
    }
}

long double Solver::approxValue(const std::pair<long double, long double> &p1,
                                const std::pair<long double, long double> &p2, long double x) {
    long double ret = p1.second + (p2.second - p1.second) / (p2.first - p1.first) * (x - p1.first);
    return ret;
}

void Solver::nextStep() {

}