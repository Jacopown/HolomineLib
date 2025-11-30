#pragma once
#include <vector>
#include <string>

using namespace std;

class DataFrame {
public:
  vector<int> timestamp; 
  vector<int> X; 
  vector<int> Y; 
  vector<int> Z; 
  DataFrame();
};

vector<vector<string>> readCSV(const string& filename); 

int printCSV(const vector<vector<string>>& data) ;
