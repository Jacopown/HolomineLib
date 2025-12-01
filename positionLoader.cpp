#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>
#include "positionLoader.h"

using namespace std;

DataFrame::DataFrame(const string& filename) {
  ifstream file(filename);
  
  if (!file.is_open()) {
      throw invalid_argument("failed to open file: " + filename);
  }
  string line;
  while (getline(file, line)) {
      vector<string> row;
      stringstream ss(line);
      string cell;
      long timeStamp;
      double X, Y, Z;

      getline(ss, cell, ';');
      timeStamp = stol(cell);

      getline(ss, cell, ';');
      X = stod(cell)/1000;

      getline(ss, cell, ';');
      Y = stod(cell)/1000;

      getline(ss, cell, ';');
      Z = stod(cell)/1000;

      DataFrame::DataPoint dataPoint = {timeStamp, X, Y, Z};

      data.push_back(dataPoint);

  }
  file.close();

  double H = data[2500].Z;
  data.erase(
    remove_if(data.begin(), data.end(), 
        [H](const DataPoint& p) {
            return abs(p.Z - H) > 1.0;
            }),
    data.end()
  );

  size = data.size();
};

size_t DataFrame::getSize() const {
  return size;
}

void DataFrame::print(size_t startingIndex, size_t lastIndex) const {
  for (size_t i = startingIndex; i < lastIndex; i++) {
    cout << data[i].timestamp << " " << data[i].X << " " << data[i].Y << " " << data[i].Z << "\n"; 
  }
}
