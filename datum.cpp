#include "datum.hpp"

Datum::Datum(int type, double* vals) : type(type), vals(vals) {}

int Datum::getType() const {
    return type;
}

double Datum::getNthVal(const int n) const {
    return vals[n];
}
