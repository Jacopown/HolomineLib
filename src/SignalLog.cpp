#include <cstddef>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>
#include "HolomineLib/Dataframe.hpp"

SignalLog::SignalLog(const std::string& filename, const long long& firstTimestamp, const long long& lastTimestamp) {
  std::ifstream file(filename);
  
  if (!file.is_open()) {
      throw std::invalid_argument("failed to open file: " + filename);
  }
  std::string line;

  //["DATE", "FREQUENCY_TX", "FREQUENCY_RX", "MOD_I", "PHASE_I", "MOD_Q", "PHASE_Q", "MOD", "PHASE"];
  if (getline(file, line))

  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string cell;
    signalDatapoint datapoint;

      getline(ss, cell, ' ');
      tm t = {};
      std::istringstream date_ss(cell);
      
      date_ss >> std::get_time(&t, "%Y/%m/%d-%H:%M:%S"); 
      
      char dot;
      int micros = 0;
      date_ss >> dot >> micros;

      time_t utc_seconds = timegm(&t);

      datapoint.timestamp = (static_cast<long long>(utc_seconds) * 1000000) + micros;

      if (datapoint.timestamp >= firstTimestamp && datapoint.timestamp <= lastTimestamp) {
        getline(ss, cell, ' ');
        datapoint.frequency = stod(cell);

        for(int i=0; i<5; ++i) {
          getline(ss, cell, ' ');
        }

        getline(ss, cell, ' ');
        datapoint.Mod = stod(cell);

        getline(ss, cell, ' ');
        datapoint.Phase = stod(cell);

        datapoint.x = 0;
        datapoint.y = 0;

        data.push_back(datapoint);
        setSize(getSize() + 1);
      }
  }
};

void SignalLog::print(size_t startingIndex, size_t lastIndex) const {
  for (size_t i = startingIndex; i < lastIndex; i++) {
    std::cout << data[i].timestamp << " " << data[i].x << " " << data[i].y << " " << data[i].frequency << " " << data[i].Mod << " " << data[i].Phase << "\n"; 
  }
}

double intep1d(double& x1, double& x2, long long& y1, long long& y2, long long& yNew) {
  // (x_2 - x_1)
  double op1 = x2 - x1; 
  // (date_new - date_1)
  double op2 = yNew - y1;
  // (date_2-date_1)
  double op3 = y2 - y1;
  // x_new = x_1 + (x_2 - x_1) * (date_new - date_1)/(date_2-date_1)
  double signalX = x1 + op1 * (op2 / op3);
  if (signalX < 0) {
  }

  return signalX;
}

void SignalLog::mapOver(const PositionLog& position) {
  std::vector<positionDatapoint> positionData = position.getData();
  int startingIndex = 0;
  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double width = std::numeric_limits<double>::min();
  double length = std::numeric_limits<double>::min();;
  for (std::size_t i = 0; i < size ; i++) {
    for (std::size_t j = startingIndex; j < position.getSize(); j++) {
      if ( positionData[j].timestamp == data[i].timestamp ) {
        setX(i, positionData[j].x);
        setY(i, positionData[j].y);

        if (positionData[j].x > width)
          width = positionData[j].x;
        if (positionData[j].y > length)
          length = positionData[j].y;
        if (positionData[j].x < minX)
          minX = positionData[j].x;
        if (positionData[j].y < minY)
          minY = positionData[j].y;

        setWidth(width);
        setLength(length);
        setMinX(minX);
        setMinY(minY);

        startingIndex = j;
        break;

      } else if (position.getData()[j].timestamp > data[i].timestamp) {
        double signalX = intep1d(positionData[j-1].x, positionData[j].x, positionData[j-1].timestamp, positionData[j].timestamp, data[i].timestamp);
        double signalY = intep1d(positionData[j-1].y, positionData[j].y, positionData[j-1].timestamp, positionData[j].timestamp, data[i].timestamp);

        setX(i, signalX);
        setY(i, signalY);

        if (signalX > width)
          width = signalX;
        if (signalY > length)
          length = signalY;
        if (signalX < minX)
          minX = signalX;
        if (signalY < minY)
          minY = signalY;
        
        setWidth(width);
        setLength(length);
        setMinX(minX);
        setMinY(minY);

        startingIndex = j;
        break;
      }
      startingIndex = j;
      
    }
  }
}
