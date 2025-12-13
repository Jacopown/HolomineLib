#include "HolomineLib/Dataframe.hpp"
#include <cstddef>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

SignalLog::SignalLog(const std::string &filename,
                     const long long &firstTimestamp,
                     const long long &lastTimestamp) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::invalid_argument("failed to open file: " + filename);
  }

  if (file.peek() == EOF) {
    setSize(0);
    return;
  }

  //["DATE", "FREQUENCY_TX", "FREQUENCY_RX", "MOD_I", "PHASE_I", "MOD_Q",
  //"PHASE_Q", "MOD", "PHASE"];
  std::string line;
  if (getline(file, line)) {
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

      datapoint.timestamp =
          (static_cast<long long>(utc_seconds) * 1000000) + micros;

      if (datapoint.timestamp >= firstTimestamp &&
          datapoint.timestamp <= lastTimestamp) {
        for (int i = 0; i < 6; ++i) {
          getline(ss, cell, ' ');
        }

        getline(ss, cell, ' ');
        datapoint.Mod = stod(cell);

        getline(ss, cell, ' ');
        datapoint.Phase = stod(cell);

        datapoint.x = 0;
        datapoint.y = 0;

        data.push_back(datapoint);
      }
    }
  }
  setSize(data.size());
};

void SignalLog::print(size_t startingIndex, size_t lastIndex) const {
  for (size_t i = startingIndex; i < lastIndex; i++) {
    std::cout << data[i].timestamp << " " << data[i].x << " " << data[i].y
              << " " << data[i].Mod << " " << data[i].Phase << "\n";
  }
}

double intep1d(double x1, double x2, long long t1, long long t2,
               long long tNew) {
  // x_new = x_1 + (x_2 - x_1) * (date_new - date_1)/(date_2-date_1)
  double div = static_cast<double>(tNew - t1) / (t2 - t1);
  return x1 + (x2 - x1) * div;
}

void SignalLog::mapOver(const PositionLog &position) {
  const std::vector<positionDatapoint> &positionData = position.getData();
  if (positionData.empty()) {
    std::cerr << "Can't map over an empty vector" << std::endl;
    return;
  } else if (data.empty()) {
    std::cerr << "Can't map an empty vector" << std::endl;
  }
  size_t startingIndex = 0;

  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double width = std::numeric_limits<double>::min();
  double length = std::numeric_limits<double>::min();

  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = startingIndex; j < positionData.size(); j++) {
      if (positionData[j].timestamp == data[i].timestamp) {
        data[i].x = positionData[j].x;
        data[i].y = positionData[j].y;

        if (data[i].x > width) width = data[i].x;
        if (data[i].y > length) length = data[i].y;
        if (data[i].x < minX) minX = data[i].x;
        if (data[i].y < minY) minY = data[i].y;

        startingIndex = j;
        break;

      } else if (positionData[j].timestamp > data[i].timestamp) {
        double signalX = intep1d(positionData[j - 1].x, positionData[j].x,
                                 positionData[j - 1].timestamp,
                                 positionData[j].timestamp, data[i].timestamp);
        double signalY = intep1d(positionData[j - 1].y, positionData[j].y,
                                 positionData[j - 1].timestamp,
                                 positionData[j].timestamp, data[i].timestamp);

        data[i].x = signalX;
        data[i].y = signalY;

        if (signalX > width) width = signalX;
        if (signalY > length) length = signalY;
        if (signalX < minX) minX = signalX;
        if (signalY < minY) minY = signalY;

        startingIndex = j - 1;
        break;
      }
    }
  }
  setWidth(width);
  setLength(length);
  setMinX(minX);
  setMinY(minY);
}
