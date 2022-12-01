#include <iostream>
#include <vector>
#include <fstream>
// these probably could've been in one header file honestly
#include "set.hpp"
#include "datum.hpp"

using namespace std;

bool readfile(string filepath);

int main(int argc, char** argv){
    if (argc < 2){
        cout << "Error: Need an argument for a file to read" << endl;
        return 1;
    }
    bool read = readfile(argv[1]);
    if (!read){
        cout << "Error: Could not read file <" << argv[1] << "> for whatever reason" << endl;
        return 1;
    }

    return 0;
}

bool readfile(string filepath){
    vector<Datum> data;
    ifstream input;
    input.open(filepath);
    if(input.is_open()){
        string line;
        while ( getline (input,line) )
        {
            if (line.size() == 0) {
                // if it somehow reads the ending new line as an entire line of size 0
                // idk I'm paranoid
                continue;
            }
            // now I have to splice line
            unsigned i;
            vector<string> rawValues;
            while (true){
                i = line.find(' ');
                if (i == string::npos)
                    break;
                rawValues.push_back(line.substr(0, i));
                line = line.substr(i+1); //skips the space
            }
            rawValues.push_back(line);
            // convert rawValues to valid Datum Object
            // first value of rawValues is the class which I will convert to an integer
            int classType = (int) stod(rawValues.at(0));
            double* nums = new double[rawValues.size() - 1];
            for (int i = 1; i < rawValues.size(); i++){
                nums[i-1] = stod(rawValues.at(i));
            }
            data.push_back(Datum(classType, nums, rawValues.size() - 1));

        }
        input.close();
        return true;
    }
    else{
        return false;
    }
}
