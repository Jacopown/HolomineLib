#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvutils.h"

using namespace std;

class DataFrame {
public:
  vector<int> timestamp; 
  vector<int> X; 
  vector<int> Y; 
  vector<int> Z; 
  DataFrame(const string& filename);

};

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
