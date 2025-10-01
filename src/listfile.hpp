#ifndef _LISTFILE_HPP_
#define _LISTFILE_HPP_

#include <string>
#include <vector>

class ListFile {
  public:
    // if no path is specified, words.txt is used
    ListFile();
    ListFile(std::string path);

    bool read(std::string path);

    std::string get_random();

  private:
    std::vector<std::string> lines;
};

#endif

