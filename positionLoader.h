#pragma once
#include <cstddef>
#include <vector>
#include <string>

using namespace std;

class DataFrame {
public:
  DataFrame(const string& filename);
  void print(size_t startingIndex, size_t lastIndex) const;
  size_t getSize() const;
private:
  struct DataPoint {
        long timestamp;
        double X, Y, Z;
    };
  vector<DataPoint> data;
  size_t size;
};
