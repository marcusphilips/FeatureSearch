#include "datum.hpp"

/// @brief Constructor to make a Datum object basically it's the data point
/// @param type e.g. Class is of type integer
/// @param vals the floating point values associated with this data point stored in a dynamically allocated array
/// @param size how big is the array passed in vals
Datum::Datum(int type, double* vals, int size) : type(type), size(size), use(false) {
    this->vals = vals;
}

/// @brief Deallocates dynamically allocated data to not create memory leaks
Datum::~Datum(){
    //delete[] vals;
}

/// @brief Constructs new Datum object using another Datum object as a parameter
/// @param d another Datum object
Datum::Datum(const Datum& d){
    this->type = d.type;
    this->size = d.size;
    this->vals = d.vals;
    // Actually want to do a shallow copy
    // vals = new double[d.size];
    // for (int i = 0; i < size; i++){
    //     vals[i] = d.vals[i];
    // }
}

/// @brief Constructs and returns the new Datum object using another Datum object after the
/// assignment operator
/// @param rhs another Datum object
/// @return the newly created Datum object
Datum& Datum::operator=(const Datum& rhs){
    type = rhs.type;
    this->size = rhs.size;
    this->vals = rhs.vals;
    // vals = new double[rhs.size];
    // for (int i = 0; i < size; i++){
    //     vals[i] = rhs.vals[i];
    // }
    return *this;
}

/// @brief return the class
/// @return the class
int Datum::getType() const {
    return type;
}

/// @brief Accesses and returns the n-th object stored in vals. 
/// @warning No bounds checking. Accessing outside of bounds creates undefined behavior
/// @param n a valid index (count from 0)
/// @return a double stored in the Datum's array of values
double Datum::getNthVal(const int n) const {
    return vals[n];
}

/// @brief Is this current Datum object equal to the 
/// @param rhs 
/// @return 
bool Datum::operator==(const Datum& rhs) const{
    // Since all the datums is shared in a single vector called data
    // Any unique datum is created only once. Thus to check if any datums
    // are equivalent. You need only to check whether the val, the dynamically
    // allocated, array are equal since each new instantiation creates a 
    // unique address
    return vals == rhs.vals;
}

int Datum::getSize() const{
    return size;
}
