#include "ansi.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "streak.hpp"

Streak::Streak() {
  path = STREAK_FILE;
  if(!read()) reset();
}

Streak::Streak(std::string path) {
  this->path = path;
  if(!read())
    throw std::runtime_error("Failed to read specified path");
}

bool Streak::read() {
  std::fstream file(path, std::ios::in);
  return file.is_open() && file.read((char *)&mTime, sizeof(mTime)).good();
}

bool Streak::write() {
  std::fstream file(path, std::ios::out);
  return file.is_open() && file.write((char *)&mTime, sizeof(mTime)).good();
}

void Streak::print() {
  std::cout << (recentlyRenewed() ? COL_STREAK_COMPLETE : 
                                  COL_STREAK_INCOMPLETE);

  if(!ongoing()) {
    reset();
    std::cout << "0 days" << COL_RESET;
    return;
  }

  bool plural = length() != 1;
  std::cout << length() << " day" << (plural ? "s" : "") << COL_RESET;
}

bool Streak::isNew() {
  return mTime.start == mTime.renew;
}

bool Streak::recentlyRenewed() {
  return time(nullptr) - DAY_FLOOR(mTime.renew) < SECS_PER_DAY && !isNew();
}

bool Streak::ongoing() {
  return  !isNew() && time(nullptr) - mTime.renew < SECS_PER_DAY;
}

size_t Streak::length() {
  return time(nullptr)/SECS_PER_DAY - mTime.start/SECS_PER_DAY;
}
