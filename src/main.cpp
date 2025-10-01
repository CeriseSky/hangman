#include "ansi.hpp"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include "gallows.hpp"
#include <iostream>
#include <set>
#include "streak.hpp"
#include <string>
#include <vector>

int main() {
  Streak streak;

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

  if(Valids.empty()) streak.renew();

  std::cout << "Streak: ";
  streak.print();
  std::cout << '\n';

  if(!streak.write()) {
    std::cerr << "Error: Failed to save streak\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
