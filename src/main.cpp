#include "HolomineLib/Dataframe.hpp"
#include <filesystem>
#include <iostream>
#include <map>

int step = 4;
namespace fs = std::filesystem;

struct pathPair {
  fs::path logPath;
  fs::path csvPath;
};

std::vector<pathPair> getValidPairs(const std::string &directoryPath) {
  std::vector<pathPair> validPairs;
  std::map<std::string, pathPair> tempMap;
  fs::path targetDir(directoryPath);

  if (!fs::exists(targetDir) or !fs::is_directory(targetDir)) {
    std::cerr << "Error: Directory does not exist.\n";
    return validPairs;
  }

  for (const auto &entry : fs::directory_iterator(targetDir)) {
    if (entry.is_regular_file()) {
      fs::path filePath = entry.path();
      std::string name = filePath.stem().string();
      std::string extension = filePath.extension().string();

      if (extension == ".log") {
        tempMap[name].logPath = filePath;
      } else if (extension == ".csv") {
        tempMap[name].csvPath = filePath;
      }
    }
  }

  for (const auto &[stem, pair] : tempMap) {
    if (!pair.logPath.empty() && !pair.csvPath.empty()) {
      validPairs.push_back(pair);
    }
  }

  return validPairs;
}

int main() {
  std::vector<pathPair> pairs = getValidPairs(
      "/home/jacopown/Repos/asmara/dataset/data/raw_data/indoor/");

  std::cout << "\nFound " << pairs.size() << " complete couples.\n";
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 1; i < pairs.size(); i++) {
    std::cout << "\nPair ready for processing:\n";
    std::cout << pairs[i].logPath.filename() << "\n";
    std::cout << pairs[i].csvPath.filename() << "\n";

    PositionLog position(pairs[i].csvPath, ';');
    std::cout << "Position size: " << position.getSize() << "\n";
    SignalLog signal(pairs[i].logPath, position.getFirstTimestamp(),
                     position.getLastTimestamp());
    std::cout << "Signal size: " << signal.getSize() << "\n";
    signal.mapOver(position);
    if (signal.getSize() >0) {
      Hologram hologram(signal, 5, 5);
      hologram.saveImage("./dump/" + pairs[i].logPath.stem().string() + "_Re.png", true);
      hologram.saveImage("./dump/" + pairs[i].logPath.stem().string() + "_Im.png", false);
    } else {
      std::cerr << pairs[i].logPath.stem().string() << " hologram is empty \n";
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Mean time: " << elapsed.count() / pairs.size() << "\n";
  std::cout << "Elapsed time: " << elapsed.count() << "\n";

  return 0;
}
