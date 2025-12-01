#include "positionLoader.h"

int main () {
  DataFrame test("/Users/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_01_A.csv");
  test.print(0, test.getSize());
}
