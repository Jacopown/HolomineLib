#include "HolomineLib/Dataframe.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <opencv2/opencv.hpp>

Hologram::Hologram(const SignalLog& signalLog, int step) {

  width = static_cast<int>(std::ceil((signalLog.getWidth() - signalLog.getMinX()) / step)) + 1;
  height = static_cast<int>(std::ceil((signalLog.getHeight() - signalLog.getMinY()) / step)) + 1;
  Mod.resize(width*height, 0.0f);
  Phase.resize(width*height, 0.0f);
  // std::vector<int> count(width*height);
  //
  // std::vector<signalDatapoint> data = signalLog.getData();  
  // double minX = signalLog.getMinX();
  // double minY = signalLog.getMinY();

  // for (size_t i = 0; i < signalLog.getSize(); i++) {
  //   double x = data[i].x;
  //   double y = data[i].y;
  //   int col = static_cast<int>((x - minX)/step);
  //   int row = static_cast<int>((y - minY)/step);
  //   Mod[row*width+col] += data[i].Mod;
  //   Phase[row*width+col] += data[i].Phase;
  //   count[row*width+col]++;
  // }

  // for (size_t i = 0; i < size ; i++) {
  //   Mod[i] = Mod[i]/count[i];
  //   Phase[i] = Phase[i]/count[i];
  //   if (i%size == 0) {
  //     std::cout << "\n";
  //   }
  //   std::cout << count[i] << " ";
  // }
}
void Hologram::print(size_t startingindex, size_t lastindex) const {
}
void Hologram::makeHologram(){
  // for (size_t i; i < size; i++) {
  //   // H = MO.*exp(1i.*PH);
  //
  //   hologram2d[i] = Mod[i]* 
  // }
}
void Hologram::saveModImage(const std::string& path){
  cv::Mat raw_matrix(height, width, CV_32FC1, const_cast<float*>(Mod.data()));
  
  cv::Mat display_image;
  cv::normalize(raw_matrix, display_image, 0, 255, cv::NORM_MINMAX, CV_8UC1);

  cv::Mat color_image;
  cv::applyColorMap(display_image, color_image, cv::COLORMAP_JET);

  bool success = cv::imwrite(path, color_image);

  if (success) {
      std::cout << "Successfully saved Mod image to: " << path << std::endl;
  } else {
      std::cerr << "Failed to save image to: " << path << std::endl;
  }
}

void Hologram::savePhaseImage(const std::string& path){
  cv::Mat raw_matrix(height, width, CV_32FC1, const_cast<float*>(Phase.data()));
  
  cv::Mat display_image;
  cv::normalize(raw_matrix, display_image, 0, 255, cv::NORM_MINMAX, CV_8UC1);

  cv::Mat color_image;
  cv::applyColorMap(display_image, color_image, cv::COLORMAP_JET);

  bool success = cv::imwrite(path, color_image);

  if (success) {
      std::cout << "Successfully saved Phase image to: " << path << std::endl;
  } else {
      std::cerr << "Failed to save image to: " << path << std::endl;
  }
}
void Hologram::saveHologramImage(const std::string& path){
}
