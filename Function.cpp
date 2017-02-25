#include "Function.h"

int stoint(std::string st)
{
    int value;
    std::istringstream buffer(st);
    buffer >> value;
    buffer.clear();
    return value;
}

double stodou(std::string st)
{
    double value;
    std::istringstream buffer(st);
    buffer >> value;
    buffer.clear();
    return value;
}

bool stobool(std::string st)
{
    bool value;
    std::istringstream buffer(st);
    buffer >> value;
    buffer.clear();
    return value;
}

std::time_t chrono(std::time_t tref)
{
    std::time_t acttime;
    time(&acttime);
    return difftime(acttime, tref);
}
