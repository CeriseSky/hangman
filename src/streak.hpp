#ifndef _STREAK_HPP_
#define _STREAK_HPP_

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <string>

#define SECS_PER_DAY 86400
#define DAY_FLOOR(x) ((x)/SECS_PER_DAY*SECS_PER_DAY)

#define STREAK_FILE "streak.dat"

#define COL_STREAK_COMPLETE "\033[31;43m"
#define COL_STREAK_INCOMPLETE "\033[37;100m"

class Streak {
  public:
    Streak();
    Streak(std::string path);

    void reset() { mTime.start = time(nullptr); mTime.renew = mTime.start; }
    void renew() { mTime.renew = time(nullptr); }

    void print(); // also resets streak if needed. Prints in colour
    bool read();
    bool write();

  private:
    // timestamps are in seconds since the epoch
    // doesn't use time_t because its size is implementation defined
    struct {
      uint64_t start;
      uint64_t renew;
    } __attribute__((packed)) mTime;

    std::string path;

    bool isNew();
    bool recentlyRenewed();
    bool ongoing();
    size_t length();
};

#endif

