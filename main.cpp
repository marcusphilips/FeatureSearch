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

    int choice;
    cout << "Enter 1 for Forward Selection or 2 for Backward Elimination" << endl;
    cin >> choice;

    // forward selection
    if (choice == 1)
    {

        /// @brief the bestFeatures stores the "history" of the tree traversal
        vector<FeatureSet> bestFeatures;

        /// @brief columnsLeft stores all the indices of the columns of data. Each level we traverse
        /// the tree, columnsLeft goes down by 1
        list<int> columnsLeft;

        // Populating ColumnsLeft with the column indices
        for (int i = 0; i < Set::getNumColumns(); i++)
        {
            columnsLeft.push_back(i);
        }

        FeatureSet defaultRate;

        // hardcoded defaultRate to be equivalent to guessing
        defaultRate.accuracy = 0.5;

        bestFeatures.push_back(defaultRate);

        // outputting data
        cout << bestFeatures.back().accuracy << " " << bestFeatures.back().toString() << endl;


        // traverse the whole tree
        while (!columnsLeft.empty())
        {
            /// @brief bestSoFar represents the set whose columns are selected from the latest element in bestFeatures.
            /// If the latest element is the default Rate, then the bestSoFar selects no columns
            Set bestSoFar;

            
            // Populating bestSoFar with the columns found already
            vector<int> bestColumns = bestFeatures.back().getColumns();
            for (unsigned j = 0; j < bestColumns.size(); j++)
            {
                bestSoFar.useColumn(bestColumns.at(j));
            }

            // find the best accuracy
            double bestRate = -1.0;
            list<int>::iterator bestRateNumber = columnsLeft.begin();

            for (list<int>::iterator it = columnsLeft.begin(); it != columnsLeft.end(); it++)
            {
                Set s = bestSoFar;

                // Add one new column to bestSoFar
                s.useColumn(*it);

                // Calculate accuracy with that one new column
                double accuracy = s.leaveOneOutAccurracy();

                // capture the best acccuracy
                if (accuracy > bestRate)
                {
                    bestRate = accuracy;
                    bestRateNumber = it;
                }
            }

            // Create new feature set from what we learned and add to bestFeatures
            FeatureSet f = bestFeatures.back();
            f.addNewColumn(*bestRateNumber);
            f.accuracy = bestRate;
            bestFeatures.push_back(f);

            // remove the column that we added from our to-do list basically. Nice O(1) operation
            columnsLeft.erase(bestRateNumber);

            // outputting data
            cout << bestFeatures.back().accuracy << " " << bestFeatures.back().toString() << endl;

        }
    }
    else
    {
        // backwards elimination
        Set s;
        FeatureSet traverser;
        int left = Set::getNumColumns();
        for (int i = 0; i < Set::getNumColumns(); i++){
            traverser.addNewColumn(i);
            s.useColumn(i);
        }

        traverser.accuracy = s.leaveOneOutAccurracy();
        cout << traverser.accuracy << " " << traverser.toString() << endl;

        while (left > 0){

            vector<int> cols = traverser.getColumns();
            
            double bestRate = -1.0;
            unsigned bestIndex = 0;
            for (unsigned i = 0; i < cols.size(); i++){
                s = Set();
                
                for (unsigned j = 0; j < cols.size(); j++){
                    // remove one column
                    if (i == j)
                        continue;
                    s.useColumn(cols.at(j));
                }
                double acccuracy = s.leaveOneOutAccurracy();

                if (acccuracy > bestRate){
                    bestIndex = i;    
                    bestRate = acccuracy; 
                }     
            }
            // update traverser
            FeatureSet next;
            for (unsigned i = 0; i < cols.size(); i++){
                if (bestIndex == i)
                    continue;
                next.addNewColumn(i);
            }

            // now traverser has one less feature
            traverser = next;
            if (traverser.getSize() != 0)
                traverser.accuracy = bestRate;
            else
                traverser.accuracy = 0.5;
            cout << traverser.accuracy << " " << traverser.toString() << endl;
            left--;

            
        }
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
            double *nums = new double[rawValues.size() - 1];
            for (unsigned i = 1; i < rawValues.size(); i++)
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
