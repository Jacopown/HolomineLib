#include "HolomineLib/Dataframe.hpp"

int step = 4;

int main () {
  PositionLog  position("/home/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_11_D.csv", ';');
  SignalLog  signal("/home/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_11_D.log", position.getFirstTimestamp(), position.getLastTimestamp());
  // Position  festo("/Users/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_01_A.csv", ';');
  // Signal  pluto("/Users/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_01_A.log", festo.getFirstTimestamp(), festo.getLastTimestamp());
  
  signal.mapOver(position);
  Hologram hologram(signal, 3, 3);
  hologram.saveImage("./testIm24.png", false);
  hologram.saveImage("./testRe24.png", true);
}
