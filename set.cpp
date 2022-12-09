#include "set.hpp"

std::vector<Datum> Set::data = std::vector<Datum>();

Set::Set(int size) : size(size)
{
    isUsing = new bool[size];
    for (int i = 0; i < size; i++)
        isUsing[i] = false;
}

/// @brief Set's the static data vector to the parameter
/// @param input a vector of Datums
void Set::setData(std::vector<Datum> &input) { data = input; }

/// @brief An almost naive implementation of nearest neighbor. Near zero optimization 
/// @param d Another datum to compare
/// @return the Datum that's the closest 
Datum& Set::nearestNeighbor(const Datum& d){
    std::vector<double> acc(data.size(), 0.0);
    // not using .at() accessor method and instead using [] to remove overhead and run faster
    for (int col = 0; col < size; col++){
        if (isUsing[col]){
            for (int i = 0; i < data.size(); i++){
                // find the differences between the two points
                double dif = data[i].getNthVal(col) - d.getNthVal(col); 
                // add the square of the difference
                acc[i] += dif * dif;
            }
        }
    }
    for (int i = 0; acc.size(); i++){
        acc[i] = std::sqrt(acc[i]);
    }
    double smallestValue = 0x7fefffffffffffff; // largest possible double value that's not NaN 
    int smallestIndex = -1;
    for (int i = 0; i < acc.size(); i++){
       if (acc[i] < smallestValue){
            if (!(data[i] == d )){ 
                // I do not care if the nearest neighbor is itself
                smallestValue = acc[i];
                smallestIndex = i;
            }
       }
    }
    return data[smallestIndex];

}

double Set::kFoldAccurracy() const {
    int k = 2;
    for (int partion = 0; partion < k; partion++){
        for (Datum& d: data){
            d.isUsing = false;
        }
    }
}
