#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <iterator>
// these probably could've been in one header file honestly
#include "set.hpp"
#include "datum.hpp"
#include "featureSet.hpp"

using namespace std;

bool readfile(string filepath);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Error: Need an argument for a file to read" << endl;
        return 1;
    }
    bool read = readfile(argv[1]);
    if (!read)
    {
        cout << "Error: Could not read file <" << argv[1] << "> for whatever reason" << endl;
        return 1;
    }
    cout << "Successfully Read File" << endl;
    vector<FeatureSet> bestFeatures;
    list<int> columnsLeft;
    const int n = Set::getNumColumns();
    for (int i = 0; i < n; i++)
    {
        columnsLeft.push_back(i);
    }
    FeatureSet defaultRate;
    defaultRate.accuracy = 0.5;
    bestFeatures.push_back(defaultRate);
    while (!columnsLeft.empty())
    {
        Set bestSoFar;
        cout << bestFeatures.back().accuracy << " " << bestFeatures.back().toString() << endl;
        vector<int> bestColumns = bestFeatures.back().getColumns();
        for (int j = 0; j < bestColumns.size(); j++){
            bestSoFar.useColumn(bestColumns.at(j));
        }
        double bestRate = -1.0;
        list<int>::iterator bestRateNumber = columnsLeft.begin();
        for (list<int>::iterator it = columnsLeft.begin(); it != columnsLeft.end(); it++)
        {
            Set s = bestSoFar;
            s.useColumn(*it);
            double accuracy = s.kFoldAccurracy();
            if (accuracy > bestRate){
                bestRate = accuracy;
                bestRateNumber = it;
            }
        }
        FeatureSet f = bestFeatures.back();
        f.addNewColumn(*bestRateNumber);
        f.accuracy = bestRate;
        bestFeatures.push_back(f);
        columnsLeft.erase(bestRateNumber);
    }

    return 0;
}

/// @brief Reads in the file. Quite tedious. I am 99% sure there is actually a faster way
/// @param filepath the filepath to the file
/// @return a bool indicating whether the file was successfully read
bool readfile(string filepath)
{
    vector<Datum> data;
    ifstream input;
    input.open(filepath);
    if (input.is_open())
    {
        string line;
        while (getline(input, line))
        {
            if (line.size() == 0)
            {
                // if it somehow reads the ending new line as an entire line of size 0
                // idk I'm paranoid
                break;
            }
            // now I have to splice line
            unsigned i;
            vector<string> rawValues;
            while (!line.empty())
            {
                i = line.find(" ");
                if (i == (unsigned)-1)
                    break;
                if (i == 0) 
                {
                    // the space character is the next character so just move over
                    line = line.substr(1);
                    continue;
                }
                rawValues.push_back(line.substr(0, i));
                line = line.substr(i + 1); // skips the space
            }
            rawValues.push_back(line + '\0');
            int classType = stoi(rawValues.at(0).substr(0, 1));
            double* nums = new double[rawValues.size() - 1];
            for (int i = 1; i < rawValues.size(); i++)
            {
                string s = rawValues.at(i);
                istringstream os(s);
                double d;
                os >> d;
                nums[i - 1] = d;
            }
            data.push_back(Datum(classType, nums, rawValues.size() - 1));
        }
        input.close();
        Set::setData(data);
        return true;
    }
    else
    {
        return false;
    }
}
