#include "Solver.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>


inline long double pw4(long double a) {
    long double a2 = a * a;
    return a2 * a2;
}

inline long double pw3(long double a) {
    long double a2 = a * a;
    return a2 * a;
}

Solver::Solver() {
}

int Solver::init(const std::string &outputDir) {
    loadValues(V, Params::V, Params::Nx, Params::dx);
    loadValues(N, Params::N, Params::Nx, Params::dx);
    loadValues(M, Params::M, Params::Nx, Params::dx);
    loadValues(H, Params::H, Params::Nx, Params::dx);

    Vfile.open(outputDir + "V.txt", std::ios_base::out);
    if (!Vfile.is_open()) {
        return 1;
    }
    Nfile.open(outputDir + "N.txt", std::ios_base::out);
    if (!Nfile.is_open()) {
        return 1;
    }
    Mfile.open(outputDir + "M.txt", std::ios_base::out);
    if (!Mfile.is_open()) {
        return 1;
    }
    Hfile.open(outputDir + "H.txt", std::ios_base::out);
    if (!Hfile.is_open()) {
        return 1;
    }

    Vfile << V.size() << " " << Params::dx << "\n";
    Vfile << (Params::Nt - 1) / Params::Times + 1 << " " << Params::dt * Params::Times << "\n";


    Nfile << V.size() << " " << Params::dx << "\n";
    Nfile << (Params::Nt - 1) / Params::Times + 1 << " " << Params::dt * Params::Times << "\n";


    Mfile << V.size() << " " << Params::dx << "\n";
    Mfile << (Params::Nt - 1) / Params::Times + 1 << " " << Params::dt * Params::Times << "\n";


    Hfile << V.size() << " " << Params::dx << "\n";
    Hfile << (Params::Nt - 1) / Params::Times + 1 << " " << Params::dt * Params::Times << "\n";

    return 0;
}

void Solver::printV() {
    printVector(Vfile, V);
}

void Solver::printN() {
    printVector(Nfile, N);
}

void Solver::printM() {
    printVector(Mfile, M);
}

void Solver::printH() {
    printVector(Hfile, H);
}

void Solver::printVector(std::fstream &file, const std::vector<long double> &r) {
    for (size_t i = 0; i < r.size(); ++i) {
        long double y = r[i];
        file << y << " ";
    }
    file << "\n";
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
        it1 = std::lower_bound(S.begin(), S.end(), std::make_pair(x, (long double) 0.0));
        if (it1 == S.end()) {
            --it1;
        }
        it2 = it1;
        if (it2 == S.begin()) {
            ++it2;
        } else {
            --it1;
        }
        dst[i] = approxValue(*it1, *it2, x);
    }
}

long double Solver::approxValue(const std::pair<long double, long double> &p1,
                                const std::pair<long double, long double> &p2, long double x) {
    long double ret = p1.second + (p2.second - p1.second) / (p2.first - p1.first) * (x - p1.first);
    return ret;
}

void Solver::nextStep() {
    nextStepN();
    nextStepM();
    nextStepH();
    nextStepV();
}

void Solver::nextStepN() {
    for (size_t i = 0; i < N.size(); ++i) {
        N[i] += Params::dt * (Params::alpN(V[i]) * (1.0L - N[i]) - Params::betN(V[i]) * N[i]);
    }
}

void Solver::nextStepM() {
    for (size_t i = 0; i < M.size(); ++i) {
        M[i] += Params::dt * (Params::alpM(V[i]) * (1.0L - M[i]) - Params::betM(V[i]) * M[i]);
    }
}

void Solver::nextStepH() {
    for (size_t i = 0; i < H.size(); ++i) {
        H[i] += Params::dt * (Params::alpH(V[i]) * (1.0L - H[i]) - Params::betH(V[i]) * H[i]);
    }
}

void Solver::nextStepV() {
    std::vector<std::vector<long double> > A;
    A.assign(V.size(), std::vector<long double>(3, 0.0L));
    A[0][1] = 1.0;
    A[V.size() - 1][1] = 1.0;
    // A * x = b
    // A[i][0] = A_i(i-1)
    // A[i][1] = A_ii
    // A[i][2] = A_i(i+1)


    std::vector<long double> b(V.size());
    b[0] = V[0];
    b[V.size() - 1] = V[V.size() - 1];

    long double C = 4.0 * Params::R * Params::dx * Params::dx / Params::d;
    for (size_t i = 1; i + 1 < V.size(); ++i) {
        b[i] = 0;
        b[i] -= Params::Cm * V[i] / Params::dt;
        b[i] -= Params::gK * pw4(N[i]) * Params::EK;
        b[i] -= Params::gNa * pw3(M[i]) * H[i] * Params::ENa;
        b[i] -= Params::gL * Params::EL;

        b[i] *= C;
    }

    for (size_t i = 1; i + 1 < V.size(); ++i) {
        A[i][0] = 1.0L;
        A[i][2] = 1.0L;

        A[i][1] = 0;
        A[i][1] -= Params::Cm / Params::dt;
        A[i][1] -= Params::gK * pw4(N[i]);
        A[i][1] -= Params::gNa * pw3(M[i]) * H[i];
        A[i][1] -= Params::gL;
        A[i][1] = -2.0L + A[i][1] * C;
    }

    tridiagonalMatrixAlgorithm(A, b, V);
}

void Solver::tridiagonalMatrixAlgorithm(const std::vector<std::vector<long double>> &A,
                                        const std::vector<long double> &B, std::vector<long double> &res) {

    size_t n = A.size();
    res.assign(n, 0.0L);

    std::vector<long double> a(n, 0.0L);
    std::vector<long double> b(n, 0.0L);
    a[1] = -A[0][2] / A[0][1];
    b[1] = B[0] / A[0][1];
    for (size_t i = 1; i + 1 < n; ++i) {
        long double denom = (A[i][1] + A[i][0] * a[i]);
        a[i + 1] = -A[i][2] / denom;
        b[i + 1] = (-A[i][0] * b[i] + B[i]) / denom;
    }
    res[n - 1] = (-A[n - 1][0] * b[n - 1] + B[n - 1]) / (A[n - 1][1] + A[n - 1][0] * a[n - 1]);
    for (int i = (int)n - 2; i >= 0; --i) {
        res[i] = a[i + 1] * res[i + 1] + b[i + 1];
    }
}

Solver::~Solver() {
    if (Vfile.is_open()) {
        Vfile.close();
    }
    if (Nfile.is_open()) {
        Hfile.close();
    }
    if (Mfile.is_open()) {
        Mfile.close();
    }
    if (Hfile.is_open()) {
        Hfile.close();
    }
}

void Solver::printValues() {
    printV();
    printN();
    printM();
    printH();
}
