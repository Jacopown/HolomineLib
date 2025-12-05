#include "HolomineLib/Dataframe.h"

int main () {
  // Position test("/home/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_01_A.csv");
  Signal  pluto("/home/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_01_A.log");
  Position  festo("/home/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_01_A.csv", ';');
  pluto.print(0, 1);
  pluto.print(pluto.getSize()-1, pluto.getSize());
  festo.print(0, 1);
  festo.print(festo.getSize()-1, festo.getSize());
}
