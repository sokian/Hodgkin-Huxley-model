#ifndef HODGKIN_HUXLEY_MODEL_DATALOADER_H
#define HODGKIN_HUXLEY_MODEL_DATALOADER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

#include "Params.h"

class DataLoader {
public:
    static int load(const std::string& filename);

private:
    static int loadConst(std::fstream &stream);
    static int loadV(std::fstream &stream);
    static int loadN(std::fstream &stream);
    static int loadM(std::fstream &stream);
    static int loadH(std::fstream &stream);
    static int loadLinearFunction(std::fstream &stream, std::vector<std::pair<long double, long double> > &ret);
};


#endif //HODGKIN_HUXLEY_MODEL_DATALOADER_H
