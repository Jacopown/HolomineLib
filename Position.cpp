#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>
#include "Dataframe.h"

using namespace std;

Position::Position(const string& filename) {
  ifstream file(filename);
  
  if (!file.is_open()) {
      throw invalid_argument("failed to open file: " + filename);
  }
  string line;
  while (getline(file, line)) {
      stringstream ss(line);
      string cell;
      datapoint datapoint;

      getline(ss, cell, ';');
      datapoint.timestamp = stol(cell);

      getline(ss, cell, ';');
      datapoint.x = stod(cell)/1000;

      getline(ss, cell, ';');
      datapoint.y = stod(cell)/1000;

      getline(ss, cell, ';');
      datapoint.z = stod(cell)/1000;

      data.push_back(datapoint);

  }

  double H = data[2500].z;
  data.erase(remove_if(data.begin(), data.end(), 
        [H](const datapoint& p) {
            return fabs(p.z - H) > 1.0;
            }),
    data.end()
  );

  size = data.size();
};

void Position::print(size_t startingIndex, size_t lastIndex) const {
  for (size_t i = startingIndex; i < lastIndex; i++) {
    cout << data[i].timestamp << " " << data[i].x << " " << data[i].y << " " << data[i].z << "\n"; 
  }
}
