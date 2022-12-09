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
    vector<Set> v;
    vector<FeatureSet> bestFeatures;
    vector<FeatureSet> fs;
    list<int> columnsLeft;
    const int n = Set::getNumColumns();
    for (int i = 0; i < n; i++)
    {
        columnsLeft.push_back(i);
    }
    v.reserve(n);
    fs.reserve(n);
    FeatureSet defaultRate;
    defaultRate.accuracy = 0.5;
    bestFeatures.push_back(defaultRate);
    while (!columnsLeft.empty())
    {
        fs.clear();
        v.clear();
        Set bestSoFar;
        vector<int> bestColumns = fs.back().getColumns();
        for (int j = 0; j < bestColumns.size(); j++){
            bestSoFar.useColumn(bestColumns.at(j));
        }
        for (list<int>::iterator it = columnsLeft.begin(); it != columnsLeft.end(); it++)
        {
            Set s = bestSoFar;
            s.useColumn(*it);
            double accuracy = s.kFoldAccurracy();
            v.push_back(s);
            FeatureSet f;
            f.addNewColumn(i);
            f.accuracy = accuracy;
            fs.push_back(f);
            cout << "Using Column " << i << " gives an accuracy of " << accuracy << endl;
        }
    }

    return 0;
}

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
            cout << line << endl;
            if (line.size() == 0)
            {
                // if it somehow reads the ending new line as an entire line of size 0
                // idk I'm paranoid
                break;
            }
            // now I have to splice line
            unsigned i;
            vector<string> rawValues;
            while (true)
            {
                i = line.find(" ");
                // cout << "i: " << i << endl;
                if (i == (unsigned)-1)
                    break;
                if (i == 0)
                {
                    line = line.substr(1);
                    continue;
                }
                rawValues.push_back(line.substr(0, i));
                // cout << rawValues.back() << endl;
                line = line.substr(i + 1); // skips the space
            }
            // cout << "remaining line <" << line << ">" << endl;
            rawValues.push_back(line + '\0');
            cout << "Last value: " << rawValues.back() << endl;
            // convert rawValues to valid Datum Object
            // first value of rawValues is the class which I will convert to an integer
            // for (int i = 0; i < rawValues.size(); i++){
            //     cout << "<" << rawValues.at(i) << ">" << endl;
            // }
            int classType = stoi(rawValues.at(0).substr(0, 1));
            double* nums = new double[rawValues.size() - 1];
            for (int i = 1; i < rawValues.size(); i++)
            {
                string s = rawValues.at(i);
                istringstream os(s);
                double d;
                os >> d;
                // cout << s << " vs " << d << endl;
                nums[i - 1] = d;
            }
            int debug;
            data.push_back(Datum(classType, nums, rawValues.size() - 1));
            // cout << "Got Data: " << data.back().getType() << endl;
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
