#pragma once
#include <cstddef>
#include <vector>
#include <string>

using namespace std;

class Dataframe {
  public:
    Dataframe() : size(0) {}
    virtual ~Dataframe() = default;

    virtual void print(size_t startingindex, size_t lastindex) const = 0;
    size_t getSize() const {return size; };

  protected:
    void setSize(int n) { size = n; };
    size_t size;
};

class Position: public Dataframe {
  public:
    Position(const string& filename, const char separator);
    void print(size_t startingindex, size_t lastindex) const override;
    long long getFirstTimestamp() const { return firstTimestamp; };
    long long getLastTimestamp() const { return lastTimestamp; };
  private:
    long long firstTimestamp;
    long long lastTimestamp;
    struct datapoint {
      long long timestamp;
      double x, y, z;
    };
    vector<datapoint> data;
};

class Signal: public Dataframe {
  public:
    Signal(const string& filename, const long long& firstTimestamp, const long long& lastTimestamp);
    void print(size_t startingindex, size_t lastindex) const override;
  private:
    struct datapoint {
      long long timestamp;
      double frequency, I, Q;
    };
    vector<datapoint> data;
};
