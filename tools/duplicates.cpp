#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  if(argc != 2) {
    std::cerr << "Format: duplicates <words list>\n";
    return EXIT_FAILURE;
  }

  std::set<std::string> uniqueLines;
  std::vector<std::string> lines;

  std::fstream file(argv[1], std::ios::in);
  if(!file.is_open()) {
    std::cerr << "Failed to read words file\n";
    return EXIT_FAILURE;
  }

  std::string line;
  while(getline(file, line))
    lines.push_back(line);
  file.close();

  for(const auto& l : lines) {
    if(uniqueLines.contains(l))
      std::cout << "Duplicate detected: \"" << l << "\"\n";
    else
      uniqueLines.insert(l);
  }

  return EXIT_SUCCESS;
}

