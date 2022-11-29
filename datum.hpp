#ifndef DATUM_HPP
#define DATUM_HPP

/// @brief Data object that holds the class and the associated values with it
class Datum {
    private:
    /// @brief Class was reserved
    int type;
    /// @brief The values stored of this paraticular datum object. The array thing is getting 
    /// annoyed so I will just use dynamically allocated arrays even though they are all
    /// the same size
    double* vals;
    public:

    // constructors

    Datum(int type, double* vals);

    // Rule of 3

    ~Datum();
    Datum(const Datum& d);
    Datum& operator=(const Datum& rhs);

    // methods or functions. I know one's for c++ and the other is for python

    int getType() const;
    double getNthVal(const int n) const;
};

#endif DATUM_HPP