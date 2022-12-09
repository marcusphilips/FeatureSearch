#include "featureSet.hpp"

FeatureSet::FeatureSet(){
    accuracy = 0.0;
}

void FeatureSet::addNewColumn(int i){
    columns.push_back(i);
    std::sort(columns.begin(), columns.end());
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
        acc += columns[i];
        if (i + 1 != columns.size()){
            acc += ", ";
        }
    }
    acc += "}";
    return acc;
}