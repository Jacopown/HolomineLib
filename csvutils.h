#pragma once
#include <vector>
#include <string>

using namespace std;

class DataFrame {
public:
  DataFrame(const string& filename);

private:
  vector<int> timestamp; 
  vector<int> X; 
  vector<int> Y; 
  vector<int> Z; 
};


vector<vector<string>> readCSV(const string& filename); 

int printCSV(const vector<vector<string>>& data) ;
