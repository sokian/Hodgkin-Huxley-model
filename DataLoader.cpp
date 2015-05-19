#include "DataLoader.h"

int
DataLoader::load(const std::string& filename) {
    std::fstream file;
    file.open(filename, std::ios_base::in);
    if (!file.is_open()) {
        std::cerr << "DataLoader::load : Data file not found" << std::endl;
        return 1;
    }

    std::string s;

    while (file >> s) {
        if (s != "BLOCK") {
            std::cerr << "DataLoader::load : WRONG FORMAT" << std::endl;
            return 1;
        }
        file >> s;
        if (s == "CONST") {
            if (loadConst(file) != 0) {
                std::cerr << "DataLoader::load : WRONG FORMAT" << std::endl;
                return 1;
            }
        }
        if (s == "V") {
            if (loadV(file) != 0) {
                std::cerr << "DataLoader::load : WRONG FORMAT" << std::endl;
                return 1;
            }
        }
        if (s == "N") {
            if (loadN(file) != 0) {
                std::cerr << "DataLoader::load : WRONG FORMAT" << std::endl;
                return 1;
            }
        }
        if (s == "M") {
            if (loadM(file) != 0) {
                std::cerr << "DataLoader::load : WRONG FORMAT" << std::endl;
                return 1;
            }
        }
        if (s == "H") {
            if (loadH(file) != 0) {
                std::cerr << "DataLoader::load : WRONG FORMAT" << std::endl;
                return 1;
            }
        }
    }
    return 0;
}

int
DataLoader::loadLinearFunction(std::fstream &stream, std::vector<std::pair<long double, long double> > &ret) {
    std::string s;
    ret.clear();
    while (stream >> s) {
        if (s == "BLOCK") {
            stream >> s;
            if (s == "END") {
                return 0;
            } else {
                return 1;
            }
        }
        long double x = std::stold(s);
        stream >> s;
        long double y = std::stold(s);
        ret.push_back(std::make_pair(x, y));
    }
    return 0;
}

int
DataLoader::loadV(std::fstream &stream) {
    return loadLinearFunction(stream, Params::V);
}
int
DataLoader::loadH(std::fstream &stream) {
    return loadLinearFunction(stream, Params::H);
}
int
DataLoader::loadN(std::fstream &stream) {
    return loadLinearFunction(stream, Params::N);
}
int
DataLoader::loadM(std::fstream &stream) {
    return loadLinearFunction(stream, Params::M);
}
int
DataLoader::loadConst(std::fstream &stream) {
    std::string s;
    while (stream >> s) {
        if (s == "BLOCK") {
            stream >> s;
            if (s == "END") {
                return 0;
            } else {
                return 1;
            }
        }
        if (s == "Nx") {
            stream >> Params::Nx;
            Params::dx = Params::LEN / Params::Nx;
            continue;
        }
        if (s == "Nt") {
            stream >> Params::Nt;
            Params::dt = Params::T / Params::Nt;
            continue;
        }
    }
}