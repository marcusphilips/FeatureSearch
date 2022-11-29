#ifndef SET_HPP
#define SET_HPP
#include <vector>
#include "datum.hpp"

class Set {
    /// @brief All the data sets share the same underlying data it's just that they choose
    /// the different column(s) of data so to speak
    static std::vector<Datum> data;
    bool* isUsing;
    int numCols;
    public:
    Set(int size);
    static void setData(std::vector<Datum>& data);
    Datum nearestNeighbor(const Datum& d);
};

#endif SET_HPP