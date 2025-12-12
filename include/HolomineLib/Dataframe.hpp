#pragma once
#include <cstddef>
#include <vector>
#include <string>

struct positionDatapoint {
  long long timestamp;
  double x, y, z;
};

struct signalDatapoint {
  long long timestamp;
  double x, y, frequency, Mod, Phase;
};

class Data {
  public:
    Data() : size(0) {}
    virtual ~Data() = default;

    size_t getSize() const {return size; };
    void setSize(int n) { size = n; };

    virtual void print(size_t startingindex, size_t lastindex) const = 0;

  protected:
    size_t size;
};

template<typename datapoint>
class LogData: public Data {
  public:
    std::vector<datapoint> getData() const {return data; };
    void setX(int index, double value) { data[index].x = value; };
    void setY(int index, double value) { data[index].y = value; };

  protected:
    std::vector<datapoint> data;
};

class PositionLog: public LogData<positionDatapoint>{
  public:
    PositionLog(const std::string& filename, const char separator);
    void print(size_t startingindex, size_t lastindex) const override;
    long long getFirstTimestamp() const { return firstTimestamp; };
    long long getLastTimestamp() const { return lastTimestamp; };
  private:
    long long firstTimestamp;
    long long lastTimestamp;
};

class SignalLog: public LogData<signalDatapoint> {
  public:
    SignalLog(const std::string& filename, const long long& firstTimestamp, const long long& lastTimestamp);

    void setMinX(double value) { minX = value; };
    void setMinY(double value) { minY = value; };
    void setWidth(double value) { width = value; };
    void setLength(double value) { length = value; };
    double getMinX() const { return minX; };
    double getMinY() const { return minY; };
    double getWidth() const { return width; };
    double getHeight() const { return length; };

    void print(size_t startingindex, size_t lastindex) const override;
    void mapOver(const PositionLog& position);
  private:
    double minX;
    double minY;
    double width;
    double length;
};

class Hologram: public Data {
  public:
    Hologram(const SignalLog& SignalLog, int step);

    void print(size_t startingindex, size_t lastindex) const override;
    void makeHologram();
    void saveModImage(const std::string& path);
    void savePhaseImage(const std::string& path);
    void saveHologramImage(const std::string& path);

  private:
    std::vector<float>Mod;
    std::vector<float>Phase;
    std::vector<float>hologram2d;
    int width;
    int height;
};
