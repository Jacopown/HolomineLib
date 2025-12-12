#include "HolomineLib/Dataframe.hpp"
#include <cmath>
#include <complex>
#include <cstddef>
#include <iostream>
#include <opencv2/opencv.hpp>

Hologram::Hologram(const SignalLog& signalLog, int xStep, int yStep) {

  width = static_cast<int>(std::ceil((signalLog.getWidth() - signalLog.getMinX()) / xStep)) + 1;
  height = static_cast<int>(std::ceil((signalLog.getHeight() - signalLog.getMinY()) / yStep)) + 1;
  std::cout << "width " << signalLog.getWidth();
  std::cout << "width " << signalLog.getHeight();
  hologram2d.resize(width*height);
  size = width*height;
  std::vector<double> count(width*height);

  std::vector<signalDatapoint> data = signalLog.getData();  
  double minX = signalLog.getMinX();
  double minY = signalLog.getMinY();

  for (size_t i = 0; i < signalLog.getSize(); i++) {
    double x = data[i].x;
    double y = data[i].y;
    double Mod = data[i].Mod;
    double Phase = data[i].Phase;
    double Re = Mod * cos(Phase);
    double Im = Mod * sin(Phase);
    int col = static_cast<int>((x - minX)/xStep);
    int row = static_cast<int>((y - minY)/yStep);
    int index = row*width+col;
    hologram2d[index] += std::complex<double>(Re, Im);
    count[index]++;
  }

  for (size_t i = 0; i < size ; i++) {
    hologram2d[i] = hologram2d[i] / count[i];
  }
}

void Hologram::saveImage(const std::string& path, bool real){
  cv::Mat complex_mat(height, width, CV_64FC2, hologram2d.data());  
  std::vector<cv::Mat> channels;
  cv::split(complex_mat, channels);

  cv::Mat visual;
  real? cv::normalize(channels[0], visual, 0, 255, cv::NORM_MINMAX, CV_8UC1): cv::normalize(channels[1], visual, 0, 255, cv::NORM_MINMAX, CV_8UC1);
  
  cv::Mat color_image;
  cv::applyColorMap(visual, color_image, cv::COLORMAP_JET);

  bool success = cv::imwrite(path, color_image);

  success? std::cout << "Successfully saved Re image to: " << path << std::endl : std::cerr << "Failed to save image to: " << path << std::endl;
}

void Hologram::print(size_t startingindex, size_t lastindex) const {
}

