#ifndef FEATURE_SET_HPP
#define FEATURE_SET_HPP
#include <vector>
#include <algorithm>

class FeatureSet {
    private:
    std::vector<int> columns;
    public:
    double accuracy;
    FeatureSet();
    void addNewColumn(int i);
    std::vector<int> getColumns() const;
    int getSize() const;
};

#endif