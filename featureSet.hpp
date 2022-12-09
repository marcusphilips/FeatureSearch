#ifndef FEATURE_SET_HPP
#define FEATURE_SET_HPP
#include <vector>
#include <string>

class FeatureSet {
    private:
    std::vector<int> columns;
    public:
    double accuracy;
    
    FeatureSet();

    void addNewColumn(const int i);
    std::vector<int> getColumns() const;
    int getSize() const;
    std::string toString() const;
   
};

#endif