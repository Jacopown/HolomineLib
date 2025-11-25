#pragma once
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> readCSV(const string& filename); 

int printCSV(const vector<vector<string>>& data) ;
