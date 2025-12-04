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

Signal::Signal(const string& filename) {
  ifstream file(filename);
  
  if (!file.is_open()) {
      throw invalid_argument("failed to open file: " + filename);
  }
  string line;

  //["DATE", "FREQUENCY_TX", "FREQUENCY_RX", "MOD_I", "PHASE_I", "MOD_Q", "PHASE_Q", "MOD", "PHASE"];
  if (getline(file, line))

  while (getline(file, line)) {
      stringstream ss(line);
      string cell;
      datapoint datapoint;

      getline(ss, cell, ' ');
      std::tm t = {};
      std::istringstream date_ss(cell);
      
      date_ss >> std::get_time(&t, "%Y/%m/%d-%H:%M:%S"); 
      
      char dot;
      int micros = 0;
      date_ss >> dot >> micros;

      time_t utc_seconds = timegm(&t);

      datapoint.timestamp = (static_cast<long long>(utc_seconds) * 1000000) + micros;

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

      data.push_back(datapoint);
      setSize(getSize() + 1);
  }
};

void Signal::print(size_t startingIndex, size_t lastIndex) const {
  for (size_t i = startingIndex; i < lastIndex; i++) {
    cout << data[i].timestamp << " " << data[i].frequency << " " << data[i].I << " " << data[i].Q << "\n"; 
  }
}
