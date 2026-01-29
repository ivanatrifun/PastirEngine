#include <logger.hpp>
#include <iostream>
#include <cstdarg>


void logger::info(const char* msg) {
    fprintf(stdout, "%s%s\n", LOGGER_INFO_PREFIX, msg);
}
void logger::warn(const char* msg) {
    fprintf(stdout, "%s%s\n", LOGGER_WARN_PREFIX, msg);
}
void logger::err(const char* msg) {
    fprintf(stderr, "%s%s\n", LOGGER_ERROR_PREFIX, msg);
}