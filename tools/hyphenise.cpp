#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  if(argc != 3) {
    std::cerr << "Format: hyphenise <wordfile in> <wordfile out>\n";
    return EXIT_FAILURE;
  }

  std::fstream input(argv[1], std::ios::in);
  if(!input.is_open()) {
    std::cerr << "Failed to open input file\n";
    return EXIT_FAILURE;
  }

  std::vector<std::string> lines;
  std::string line;

  while(getline(input, line))
    if(line.find("-") != line.npos) lines.push_back(line);

  input.close();
  std::fstream output(argv[2], std::ios::out);
  if(!output.is_open()) {
    std::cerr << "Failed to open output file\n";
    return EXIT_FAILURE;
  }

  for(const auto& l : lines)
    output << l << '\n';

  std::cout << lines.size() << " lines copied\n";
  return EXIT_FAILURE;
}

