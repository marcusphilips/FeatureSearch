#include "featureSet.hpp"

using namespace std;

/// @brief Constructs a new FeatureSet
FeatureSet::FeatureSet(){
    accuracy = 0.0;
}

/// @brief Adds a column which means the column list is in order of how it's added
/// @param i column index
void FeatureSet::addNewColumn(const int i){
    columns.push_back(i);
}

/// @brief How many features basically this Feature Set object is tracking
/// @return number of features tracked in form of an integer
int FeatureSet::getSize()const{
    return columns.size();
}

/// @brief Returns a vector representing the features used 
/// @return vector<int>
std::vector<int> FeatureSet::getColumns() const{
    return columns;
}

/// @brief Returns a nicely formatted toString representation of the FeatureSet
/// @return a string
std::string FeatureSet::toString() const{
    std::string acc = "{";

    for (unsigned i = 0; i < columns.size(); i++){
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
