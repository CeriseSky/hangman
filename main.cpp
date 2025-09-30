#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// probably not the best solution...
// What can I say, I'm pretty lazy
const char *gallows[] = {
  " +--+\n"
  " o  |\n"
  "/|\\ |\n"
  "/ \\ |\n"
  "    |\n"
  "----+",

  " +--+\n"
  " o  |\n"
  "/|\\ |\n"
  "/   |\n"
  "    |\n"
  "----+",

  " +--+\n"
  " o  |\n"
  "/|\\ |\n"
  "    |\n"
  "    |\n"
  "----+",

  " +--+\n"
  " o  |\n"
  " |\\ |\n"
  "    |\n"
  "    |\n"
  "----+",

  " +--+\n"
  " o  |\n"
  " |  |\n"
  "    |\n"
  "    |\n"
  "----+",

  " +--+\n"
  " o  |\n"
  "    |\n"
  "    |\n"
  "    |\n"
  "----+",

  " +--+\n"
  "    |\n"
  "    |\n"
  "    |\n"
  "    |\n"
  "----+",

  "     \n"
  "    |\n"
  "    |\n"
  "    |\n"
  "    |\n"
  "----+",

  "     \n"
  "     \n"
  "     \n"
  "     \n"
  "     \n"
  "----+",

  "Hangman is safe!"
};

#define STREAK_COL_COMPLETE "\033[31;43m"
#define STREAK_COL_INCOMPLETE "\033[37;100m"
#define COL_RESET "\033[0m"

#define CLEAR_SCR "\033[2J\033[H"

#define SECS_PER_DAY 86400
#define DAY_FLOOR(x) ((x)/SECS_PER_DAY*SECS_PER_DAY)

#define STREAK_FILE "streak.dat"

class Streak {
  public:
    // Timestamps are in days since the epoch
    uint64_t start;
    uint64_t renew;

    Streak() { reset(); }

    // prints number of days into the streak, in the correct colour,
    // and also resets the streak if it needs to
    void print() {
      uint64_t now = time(nullptr);
      bool recentlyRenewed = now - DAY_FLOOR(renew) <
                             SECS_PER_DAY && !isNew();
      std::cout << (recentlyRenewed ? STREAK_COL_COMPLETE : 
                                      STREAK_COL_INCOMPLETE);

      bool streakLost = isNew() || now - renew >= SECS_PER_DAY;
      if(streakLost) {
        reset();
        std::cout << "0 days" << COL_RESET;
        return;
      }

      uint64_t days = now / SECS_PER_DAY
                    - start / SECS_PER_DAY
                    + recentlyRenewed;
      std::cout << days << " day" << (days != 1 ? "s" : "") << COL_RESET;
    }

    void reset() { start = time(nullptr); renew = start; }

  private:
      bool isNew() { return start == renew; }
};

int main() {
  Streak streak;

  std::fstream streakFile(STREAK_FILE, std::ios::in);
  if(!streakFile.is_open() ||
     !streakFile.read((char *)&streak,
                      sizeof(streak))
                .good()) {
    std::cerr << "Warning: Failed to read streak file, starting new one\n";
    streak.reset(); // necessary in case of a partial read
  }
  streakFile.close();

  std::fstream words("words.txt", std::ios::in);
  if(!words.is_open()) {
    std::cerr << "Failed to open words.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::string> lines;
  std::string line;
  while(std::getline(words, line))
    lines.push_back(line);

  words.close();

  std::fstream crimes("crimes.txt", std::ios::in);
  if(!crimes.is_open()) {
    std::cerr << "Failed to open crimes.txt";
    return EXIT_FAILURE;
  }

  std::vector<std::string> CrimeList;
  while(std::getline(crimes, line))
    CrimeList.push_back(line);

  srand(clock());
  std::string CorrectWord = lines[rand() % lines.size()];
  std::string crime = CrimeList[rand() % CrimeList.size()];

  std::set<char> Valids, Corrects, Incorrects;
  for(const char c : CorrectWord)
    Valids.insert(tolower(c));

  size_t StrikesLeft = sizeof(gallows)/sizeof(char *);
  while(Valids.size() && StrikesLeft) {
    std::cout << CLEAR_SCR;

    std::cout << "Streak: ";
    streak.print();
    std::cout << '\n';

    // safe because loop exits if StrikesLeft == 0
    std::cout << gallows[StrikesLeft - 1] << "\n" <<
                 "Crime: He " << crime << "...\n\n";

    std::cout << "Word: ";
    for(const char c : CorrectWord)
      std::cout << (Corrects.contains(tolower(c)) ? c : '_');
    std::cout << '\n';

    std::cout << "Incorrect guesses: ";
    for(const char c : Incorrects)
      std::cout << c;
    std::cout << '\n';

    char guess;
    std::cout << "Enter guess: ";
    std::cin >> guess;
    guess = tolower(guess);
    std::cout << "\n";

    if(Valids.contains(guess)) {
      Valids.erase(guess);
      Corrects.insert(guess);
    } else {
      Incorrects.insert(guess);
      StrikesLeft--;
    }
  }

  std::cout << '\n' << (Valids.empty() ? "Well done!" :
                                         "Better luck next time!")
                    << '\n';

  std::cout << "The word was: " << CorrectWord << '\n';

  if(Valids.empty())
    streak.renew = time(nullptr);

  streakFile.open("streak.dat", std::ios::out);
  if(!streakFile.is_open() ||
     !streakFile.write((char *)&streak,
                       sizeof(streak))
                .good()) {
    std::cerr << "Error: Failed to save streak\n";
    return EXIT_FAILURE;
  }
  streakFile.close();

  std::cout << "Streak: ";
  streak.print();
  std::cout << '\n';

  return EXIT_SUCCESS;
}
