#pragma once
#ifndef __UTILITY_HPP
#define __UTILITY_HPP

#include <data_types.hpp>
#include <vector>

namespace util {
    std::vector<Rectu> loadTiles(const char* tilestructfile);
} // namespace util


#endif