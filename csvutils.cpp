#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include "csvutils.h"

using namespace std;

DataFrame::DataFrame(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::invalid_argument("failed to open file: " + filename);
    }
    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        getline(ss, cell, ';');
        timestamp.push_back(stoi(cell));

        getline(ss, cell, ';');
        X.push_back(stoi(cell));

        getline(ss, cell, ';');
        Y.push_back(stoi(cell));

        getline(ss, cell, ';');
        Z.push_back(stoi(cell));
    }
    file.close();
};

vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "failed to open file: " << filename << endl;
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
