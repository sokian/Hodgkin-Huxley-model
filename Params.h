#ifndef HODGKIN_HUXLEY_MODEL_PARAMS_H
#define HODGKIN_HUXLEY_MODEL_PARAMS_H

#include <cmath>
#include <map>
#include <vector>

namespace Params {
    extern long double d;
    extern long double R;
    extern long double Cm;
    extern long double gK;
    extern long double ER;
    extern long double EK;
    extern long double ENa;
    extern long double EL;
    extern long double gNa;
    extern long double GL;

    extern long double dt;
    extern long double dx;

    extern size_t Nx;
    extern size_t Nt;
    extern long double LEN;
    extern long double T;

    extern std::vector<std::pair<long double, long double> > V;
    extern std::vector<std::pair<long double, long double> > N;
    extern std::vector<std::pair<long double, long double> > M;
    extern std::vector<std::pair<long double, long double> > H;

    inline long double alpN(long double V) {
        return 0.01 * (10 - V) / (std::exp((10 - V) / 10) - 1);
    }
    inline long double alpM(long double V) {
        return 0.1 * (25 - V) / (std::exp((25 - V) / 10) - 1);
    }
    inline long double alpH(long double V) {
        return 0.07 * std::exp(-V / 20);
    }

    inline long double betN(long double V) {
        return 0.125 * std::exp(-V / 80);
    }
    inline long double betM(long double V) {
        return 4 * std::exp(-V / 18);
    }
    inline long double betH(long double V) {
        return 1.0 / (std::exp((30 -  V) / 10) + 1);
    }
};

#endif //HODGKIN_HUXLEY_MODEL_PARAMS_H
