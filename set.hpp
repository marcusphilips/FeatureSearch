#ifndef SET_HPP
#define SET_HPP
#include <vector>
#include <cmath>
#include "datum.hpp"

class Set {
    /// @brief All the data sets share the same underlying data it's just that they choose
    /// the different column(s) of data so to speak
    static std::vector<Datum> data;
    bool* isUsing;
    int size;
    public:

    // constructor

    Set(int size);

    // TODO: Rule of Three

    ~Set();
    Set(const Set& s);
    Set& operator=(const Set& rhs);

    // functions

    static void setData(std::vector<Datum>& data);
    Datum& nearestNeighbor(const Datum& d);
    double kFoldAccurracy() const;
};

#endif 