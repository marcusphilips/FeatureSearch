#include <iostream>
#include <vector>
#include <fstream>

// these probably could've been in one header file honestly
#include "set.hpp"
#include "datum.hpp"

using namespace std;

bool readfile(string filepath);

int main(int argc, char** argv){
    readfile(argv[1]);
    return 0;
}

bool readfile(string filepath){
    ifstream input;
    input.open(filepath);
    if(input.is_open()){
        string line;
        while ( getline (input,line) )
        {
        cout << line << '\n';
        }
        input.close();
        return true;
    }
    else{
        return false;
    }

}
