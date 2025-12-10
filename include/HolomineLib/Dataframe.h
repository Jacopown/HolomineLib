#pragma once
#include <cstddef>
#include <vector>
#include <string>

template<typename datapoint>
class Dataframe {
  public:
    Dataframe() : size(0) {}
    virtual ~Dataframe() = default;

    std::vector<datapoint> getData() const {return data; };
    size_t getSize() const {return size; };

    void setX(int index, double value) { data[index].x = value; };
    void setY(int index, double value) { data[index].y = value; };
    void setSize(int n) { size = n; };

    virtual void print(size_t startingindex, size_t lastindex) const = 0;

  protected:
    size_t size;
    std::vector<datapoint> data;
};

struct positionDatapoint {
  long long timestamp;
  double x, y, z;
};

class Position: public Dataframe<positionDatapoint>{
  public:
    Position(const std::string& filename, const char separator);
    void print(size_t startingindex, size_t lastindex) const override;
    long long getFirstTimestamp() const { return firstTimestamp; };
    long long getLastTimestamp() const { return lastTimestamp; };
  private:
    long long firstTimestamp;
    long long lastTimestamp;
};

struct signalDatapoint {
  long long timestamp;
  double x, y, frequency, I, Q;
};

class Signal: public Dataframe<signalDatapoint> {
  public:
    Signal(const std::string& filename, const long long& firstTimestamp, const long long& lastTimestamp);
    void print(size_t startingindex, size_t lastindex) const override;
};
