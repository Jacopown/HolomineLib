#include "HolomineLib/map.h"
#include "HolomineLib/Dataframe.h"
#include <iostream>
#include <vector>

double intep1d(double& positionX1, double& positionX2, long long& positionTimestamp1, long long& positionTimestamp2, long long& signalTimestamp) {
  // (x_2 - x_1)
  double op1 = positionX2 - positionX1; 
  // (date_new - date_1)
  double op2 = signalTimestamp - positionTimestamp1;
  // (date_2-date_1)
  double op3 = positionTimestamp2 - positionTimestamp1;
  // x_new = x_1 + (x_2 - x_1) * (date_new - date_1)/(date_2-date_1)
  double signalX = positionX1 + op1 * (op2 / op3);
  if (signalX < 0) {
    // std::cout << "positionX1" << positionX1 << "\n";
    // std::cout << "positionX2" << positionX2 << "\n";
    // std::cout << "op1 " << op1 << "\n";
    // std::cout << "op2 " << op2 << "\n";
    // std::cout << "op3 " << op3 << "\n";
    // std::cout << "(op2/op3) " << op2 / op3 << "\n";
    // std::cout << "op1*(op2/op3) " << op1* (op2 / op3) << "\n";
    // std::cout << "signalX " << signalX << "\n";
  }

  return signalX;
}

void map(const Position& position, Signal& signal) {
  std::vector<positionDatapoint> positionData = position.getData();
  std::vector<signalDatapoint> signalData = signal.getData();
  int startingIndex = 0;
  for (std::size_t i = 0; i<signal.getSize(); i++) {
    for (std::size_t j = startingIndex; j<position.getSize(); j++) {
      if ( positionData[j].timestamp == signalData[i].timestamp ) {
        // std::cout << "Pos Time:" << positionData[j].timestamp << "==" << "Signal Time:" << signalData[i].timestamp << "\n";
        signal.setX(i, positionData[j].x);
        // std::cout << "Pos x:" << positionData[j].x << "\n";
        signal.setY(i, positionData[j].y);
        // std::cout << "Pos y:" << positionData[j].y;
        
        startingIndex = j;
        break;
      } else if (position.getData()[j].timestamp > signalData[i].timestamp) {
        double signalX = intep1d(positionData[j-1].x, positionData[j].x, positionData[j-1].timestamp, positionData[j].timestamp, signalData[i].timestamp);
        signal.setX(i, signalX);
        // if (signalX < 0) {
          // std::cout << "Pos Time:" << positionData[j].timestamp << ">" << "Signal Time:" << signalData[i].timestamp << "\n";
          // std::cout << "Signal x_1:" << signalData[j-1].x << "\n";
          // std::cout << "Signal x_2:" << signalData[j-1].x << "\n";
          // std::cout << "Position date1:" << positionData[j-1].timestamp << "\n";
          // std::cout << "Position date2:" << positionData[j].timestamp << "\n";
          // std::cout << "Pos x:" << signalX << "\n";
        // }
        double signalY = intep1d(positionData[j-1].y, positionData[j].y, positionData[j-1].timestamp, positionData[j].timestamp, signalData[i].timestamp);
        signal.setY(i, signalY);
        // if (signalY < 0) {
          // std::cout << "Pos Time:" << positionData[j].timestamp << ">" << "Signal Time:" << signalData[i].timestamp << "\n";
          // std::cout << "Signal y_1:" << signalData[j-1].y << "\n";
          // std::cout << "Signal y_2:" << signalData[j-1].y << "\n";
          // std::cout << "Position date1:" << positionData[j-1].timestamp << "\n";
          // std::cout << "Position date2:" << positionData[j].timestamp << "\n";
          // std::cout << "Pos y:" << signalY << "\n";
        // }

        startingIndex = j;
        break;
      }
      startingIndex = j;
      
    }
  }
}
