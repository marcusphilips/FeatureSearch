#ifndef SET_HPP
#define SET_HPP
#include <vector>
#include <cmath>
#include "datum.hpp"

class Set {
    /// @brief All the data sets share the same underlying data it's just that they choose
    /// the different column(s) of data so to speak
    static std::vector<Datum> data;
    /// @brief A dynamically allocated array that doesn't really change size that correalates to whether a column 
    /// is to be used
    bool* isUsing;
    /// @brief Size denotes the number of columns i.e. responding variables not the number of Datum elements in the 
    /// data set
    int size;
    public:

    // constructor

    Set();

    // Rule of Three

    ~Set();
    Set(const Set& s);
    Set& operator=(const Set& rhs);

    // functions
   
    static void setData(std::vector<Datum>& data);
    static int getNumColumns();

    int nearestNeighbor(const Datum& d) const;
    double leaveOneOutAccurracy() const; 
    void useColumn(int index);
};

#endif 