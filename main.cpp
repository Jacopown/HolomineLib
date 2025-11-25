#include "csvutils.h"

int main () {
        vector<vector<string>> data = readCSV("/Users/jacopown/Repos/asmara/dataset/data/raw_data/indoor/in_bas_01_A.csv");
        printCSV(data);
        return 0;
}
