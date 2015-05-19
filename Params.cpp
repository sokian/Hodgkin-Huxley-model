#include "Params.h"

namespace Params {
    long double d = 0.5;
    long double R = 1;
    long double Cm = 1;
    long double gK = 36;
    long double ER = 1;
    long double EK = ER - 12.0;
    long double ENa = ER + 115;
    long double EL = ER + 10.613;
    long double gNa = 120;
    long double GL = 0.3;

    long double dt;
    long double dx;

    size_t Nx;
    size_t Nt;
    long double LEN = 100;
    long double T = 100;




    std::vector<std::pair<long double, long double> > V;
    std::vector<std::pair<long double, long double> > N;
    std::vector<std::pair<long double, long double> > M;
    std::vector<std::pair<long double, long double> > H;
};