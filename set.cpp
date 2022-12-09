#include "set.hpp"

std::vector<Datum> Set::data = std::vector<Datum>();

Set::Set() : size(data.size())
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
/// @return the class/type of the datum that's closest
int Set::nearestNeighbor(const Datum& d) const {
    std::vector<double> acc;
    // just reserve a bunch of memory to speed up
    acc.reserve(data.size());
    // not using .at() accessor method and instead using [] to remove overhead and run faster
    // for (int col = 0; col < size; col++){
    //     if (isUsing[col]){
    //         for (int i = 0; i < data.size(); i++){
    //             if (!data.at(i).isUsed() || d == )
    //                 continue;
    //             // find the differences between the two points
    //             double dif = data[i].getNthVal(col) - d.getNthVal(col); 
    //             // add the square of the difference
    //             acc.push_back(dif * dif);
    //         }
    //     }
    // }
    for (int i = 0; i < data.size(); i++){
        if (data[i] == d){
            // do not compare a datum to itself
            continue;
        }
        if (!data[i].isUsed()){
            // do not use datums that are hidden in k-cross
            continue;
        }
        acc.push_back(0.0);
        for (int col = 0; col < size; col++){
            if (!isUsing[col])
                continue;
            double dif = data[i].getNthVal(col) - d.getNthVal(col); 
            acc.back() += dif*dif;
        }
    }
    for (int i = 0; acc.size(); i++){
        acc[i] = std::sqrt(acc[i]);
    }
    double smallestValue = acc[0]; // largest
    int smallestIndex = 0;
    for (int i = 0; i < acc.size(); i++){
       if (acc[i] < smallestValue){
            if (!(data[i] == d )){ 
                // I do not care if the nearest neighbor is itself
                smallestValue = acc[i];
                smallestIndex = i;
            }
       }
    }
    return data[smallestIndex].getType();
   
}

double Set::kFoldAccurracy() const {
    const int k = 5;
    const int n = data.size();
    int total = 0;
    int correct = 0;
    for (int partition = 0; partition < k; partition++){
        // k select
        for (int i = 0; i < n; i++){
            if (i > (double)n*partition/k && i < (double)n*(partition + 1)/k)
                data[i].doUse();
            else
                data[i].doNotUse();
        }
        // test nearest neighbor
        for (int i = 0; i < n; i++){
            total++;
            if (data[i].getType() == nearestNeighbor(data[i])){
                correct++;
            }
        }
    }
    return (double) correct / total;
}

Set::~Set(){
    delete[] isUsing;
}

void Set::useColumn(int index){
    isUsing[index] = true;
}
