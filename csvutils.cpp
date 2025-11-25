#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvutils.h"

using namespace std;

class DataFrame {
public:
        vector<int> 
        DataFrame();
        DataFrame(DataFrame &&) = default;
        DataFrame(const DataFrame &) = default;
        DataFrame &operator=(DataFrame &&) = default;
        DataFrame &operator=(const DataFrame &) = default;
        ~DataFrame();

private:
       0x01 02 03 08
               08 03 02 01 

0001 = 1
0010 = 2
0011 = 3
1000 = 8

1000 = 8
0011 = 3
0010 = 2
0001 = 1

};

DataFrame::DataFrame() {
}

DataFrame::~DataFrame() {
}

vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

int printCSV(const vector<vector<string>>& data) {
    for (const vector<string>& row : data) {
        for (const string& cell : row) {
            cout << cell << "\t";
        }
        cout << endl;
    }

    return 0;
}
