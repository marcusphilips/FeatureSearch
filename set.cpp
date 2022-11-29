#include "set.hpp"

std::vector<Datum> Set::data = std::vector<Datum>();

Set::Set(int size) : numCols(size)
{
    isUsing = new bool[size];
    for (int i = 0; i < size; i++)
        isUsing[i] = false;
}

void Set::setData(std::vector<Datum> &input) { data = input; }

