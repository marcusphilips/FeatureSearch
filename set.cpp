#include "set.hpp"

std::vector<Datum> Set::data = std::vector<Datum>();

Set::Set() : size(data[0].getSize())
{
    isUsing = new bool[size];
    for (int i = 0; i < size; i++)
        isUsing[i] = false;
}

/// @brief Set's the static data vector to the parameter
/// @param input a vector of Datums
void Set::setData(std::vector<Datum> &input) { data = input; }

int Set::getNumColumns()
{
    return data[0].getSize();
}

/// @brief An almost naive implementation of nearest neighbor. Near zero optimization
/// @param d Another datum to compare
/// @return the class/type of the datum that's closest
int Set::nearestNeighbor(const Datum &d) const
{
    std::vector<double> acc;
    // just reserve a bunch of memory to speed up
    acc.reserve(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == d)
        {
            // do not compare a datum to itself but to preserve the alignment just add
            // massive value
            acc.push_back(1000000.0);
            continue;
        }
        // if (!data[i].isUsed()){
        //     // do not use datums that are hidden in k-cross
        //     acc.push_back(1000000.0);
        //     continue;
        // }
        acc.push_back(0.0);
        for (int col = 0; col < size; col++)
        {
            if (!isUsing[col])
                continue;
            double dif = data[i].getNthVal(col) - d.getNthVal(col);
            acc.back() += dif * dif;
        }
    }
    for (int i = 0; i < acc.size(); i++)
    {
        acc[i] = std::sqrt(acc[i]);
    }
    // std::cout << "Distances: ";
    // for (int i = 0; i < acc.size(); i++){
    //     std::cout << acc[i] << " " ;
    // }
    // std::cout << std::endl;
    double smallestValue = acc[0]; // largest
    // should be read as "index of the smallest"
    int smallestIndex = 0;
    for (int i = 0; i < acc.size(); i++)
    {
        if (acc[i] < smallestValue)
        {
            if (!(data[i] == d))
            {
                // I do not care if the nearest neighbor is itself
                smallestValue = acc[i];
                smallestIndex = i;
            }
        }
    }
    // std::cout << "For " << d.getType() << " with values "
    //     << d.getNthVal(0) << ", " << d.getNthVal(1) << std::endl;
    // std::cout << "The nearest neighbor is " << data[smallestIndex].getType() << std::endl;
    // exit(0);
    return data[smallestIndex].getType();
}

double Set::leaveOneOutAccurracy() const
{
    const int n = data.size();
    int total = 0;
    int correct = 0;
    // test nearest neighbor
    for (int i = 0; i < n; i++)
    {
        total++;
        if (data[i].getType() == nearestNeighbor(data[i]))
        {
            correct++;
        }
    }
    //}
    return (double)correct / total;
}

Set::~Set()
{
    // Sorry but I am paranoid about Segmentation faults
    // delete[] isUsing;
}

Set::Set(const Set &s)
{
    this->size = s.size;
    bool *n = new bool[s.size];
    for (int i = 0; i < s.size; i++)
    {
        n[i] = s.isUsing[i];
    }
    this->isUsing = n;
}

Set &Set::operator=(const Set &rhs)
{
    isUsing = new bool[rhs.size];
    for (int i = 0; i < rhs.size; i++)
    {
        isUsing[i] = rhs.isUsing[i];
    }
    return *this;
}

void Set::useColumn(int index)
{
    isUsing[index] = true;
}
