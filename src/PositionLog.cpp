#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>
#include "HolomineLib/Dataframe.hpp"

PositionLog::PositionLog(const std::string& filename, const char separator) {
  std::ifstream file(filename);
  
  if (!file.is_open()) {
      throw std::invalid_argument("failed to open file: " + filename);
  }

  if (file.peek() == EOF) {
    setSize(0);
    return;
  }
  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string cell;
      positionDatapoint datapoint;

      getline(ss, cell, separator);
      datapoint.timestamp = stoll(cell)*1000;

      getline(ss, cell, separator);
      datapoint.x = stod(cell)/1000;

      getline(ss, cell, separator);
      datapoint.y = stod(cell)/1000;

      getline(ss, cell, separator);
      datapoint.z = stod(cell)/1000;

      data.push_back(datapoint);

  }

  // TODO: Remove hard coded check spot
  double H = data[2500].z;
  data.erase(remove_if(data.begin(), data.end(), 
        [H](const positionDatapoint& p) {
            return fabs(p.z - H) > 1.0;
            }),
    data.end()
  );
  firstTimestamp = data[0].timestamp;
  lastTimestamp = data[data.size()-1].timestamp;

  size = data.size();
};

void PositionLog::print(size_t startingIndex, size_t lastIndex) const {
  for (size_t i = startingIndex; i < lastIndex; i++) {
    std::cout << data[i].timestamp << " " << data[i].x << " " << data[i].y << " " << data[i].z << "\n"; 
  }
}
