#include <fstream>
#include "listfile.hpp"
#include <random>
#include <stdexcept>

ListFile::ListFile() {
  if(!read("words.txt"))
    throw std::runtime_error("Failed to open list file");
}

ListFile::ListFile(std::string path) {
  if(!read(path))
    throw std::runtime_error("Failed to open list file");
}

bool ListFile::read(std::string path) {
  std::fstream file(path, std::ios::in);
  if(!file.is_open())
    return false;

  std::string line;
  while(getline(file, line))
    if(line.length() > 0)
      lines.push_back(line);

  return lines.size() > 0;
}

std::string ListFile::get_random() {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_int_distribution<> dist(0, lines.size() - 1);
  return lines[dist(gen)];
}

