#include <cstddef>
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

int main() {
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

  // TODO: reimplement using the C++11 random library
  srand(clock());
  std::string CorrectWord = lines[rand() % lines.size()];

  // Maybe not the best solution
  std::set<char> Valids, Corrects, Incorrects;
  for(const char c : CorrectWord)
    Valids.insert(tolower(c));

  size_t StrikesLeft = sizeof(gallows)/sizeof(char *);
  while(Valids.size() && StrikesLeft) {
    // safe because loop exits if StrikesLeft == 0
    std::cout << gallows[StrikesLeft - 1] << "\n\n";

    std::cout << "Word: ";
    for(const char c : CorrectWord)
      std::cout << (Corrects.contains(c) ? c : '_');
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

  return EXIT_SUCCESS;
}
