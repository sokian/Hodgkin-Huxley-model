#ifndef HODGKIN_HUXLEY_MODEL_LOGGER_H
#define HODGKIN_HUXLEY_MODEL_LOGGER_H

#include <cstdio>
#include <cstdarg>

enum LOG_LEVEL {
    ERROR = 0,
    INFO = 1,
    DEBUG = 2,
    TRACE = 3
};

int MAX_LOG_LEVEL;

const char * getLevelString(LOG_LEVEL level) {
    switch (level) {
        case ERROR:
            return "ERR";
        case INFO:
            return "INF";
        case DEBUG:
            return "DEB";
        case TRACE:
            return "TRA";
        default:
            return "";
    }
}

void log(LOG_LEVEL level, const char *format, ...) {

}

#endif //HODGKIN_HUXLEY_MODEL_LOGGER_H
