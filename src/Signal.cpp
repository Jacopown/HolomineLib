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
#include "HolomineLib/Dataframe.h"

Signal::Signal(const std::string& filename, const long long& firstTimestamp, const long long& lastTimestamp) {
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
        double Mod = stod(cell);

        getline(ss, cell, ' ');
        double Phase = stod(cell);

        datapoint.I = Mod*sin(Phase);
        datapoint.Q = Mod*cos(Phase);
        datapoint.x = 0;
        datapoint.y = 0;

        data.push_back(datapoint);
        setSize(getSize() + 1);
      }
  }
};

void Signal::print(size_t startingIndex, size_t lastIndex) const {
  for (size_t i = startingIndex; i < lastIndex; i++) {
    std::cout << data[i].timestamp << " " << data[i].x << " " << data[i].y << " " << data[i].frequency << " " << data[i].I << " " << data[i].Q << "\n"; 
  }
}
