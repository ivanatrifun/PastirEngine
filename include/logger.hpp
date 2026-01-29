#pragma once
#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#define LOGGER_INFO_PREFIX ""
#define LOGGER_WARN_PREFIX "[WARN] "
#define LOGGER_ERROR_PREFIX "[ERROR] "

namespace logger {
    /**
     * Prints text as info
     */
    void info(const char* msg);
    /**
     * Prints text as a warning
     */
    void warn(const char* msg);
    /**
     * Prints text as an error
     */
    void err(const char* msg);

} // namespace logger


#endif