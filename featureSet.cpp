#include "featureSet.hpp"

using namespace std;

FeatureSet::FeatureSet(){
    accuracy = 0.0;
    lastAdded = -1;
}

void FeatureSet::addNewColumn(const int i){
    lastAdded = i;
    columns.push_back(i);
}

int FeatureSet::getSize()const{
    return columns.size();
}

std::vector<int> FeatureSet::getColumns() const{
    return columns;
}

std::string FeatureSet::toString() const{
    std::string acc = "{";
    for (int i = 0; i < columns.size(); i++){
        // to account that the first column is in code is 0
        // but outside speak we count from 1
        acc += to_string(columns[i] + 1);
        if (i + 1 != columns.size()){
            acc += ", ";
        }
    }
    acc += "}";
    return acc;
}

int FeatureSet::getLastAdded() const{
    return lastAdded;
}