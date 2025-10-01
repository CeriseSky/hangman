#include "ansi.hpp"
#include <cstddef>
#include <cstdlib>
#include "gallows.hpp"
#include <iostream>
#include "listfile.hpp"
#include <set>
#include "streak.hpp"
#include <string>

int main() {
  Streak streak;
  ListFile words("words.txt"), crimes("crimes.txt");

  std::string CorrectWord = words.get_random();
  std::string crime = crimes.get_random();

  std::set<char> Valids, Corrects, Incorrects;
  for(const char c : CorrectWord)
    if(std::isalpha(c))
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
      std::cout << (!std::isalpha(c) || Corrects.contains(tolower(c)) ?
                    c : '_');
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
