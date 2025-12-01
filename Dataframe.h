#pragma once
#include <cstddef>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Dataframe {
  public:
    Dataframe() : size(0) {}
    virtual ~Dataframe() = default;

    virtual void print(size_t startingindex, size_t lastindex) const = 0;
    size_t getSize() const {return size; };

  protected:
    size_t size;
};

class Position: public Dataframe {
  public:
    Position(const string& filename);
    void print(size_t startingindex, size_t lastindex) const override;
  private:
    struct datapoint {
      long timestamp;
      double x, y, z;
    };
    vector<datapoint> data;
};

class Signal: public Dataframe {
  public:
    Signal(const string& filename);
    void print(size_t startingindex, size_t lastindex) const override;
  private:
    struct datapoint {
      long timestamp;
      double P, P_I, P_Q;
    };
    vector<datapoint> data;
};
