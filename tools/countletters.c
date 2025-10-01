#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_LENGTH ('Z' - 'A' + 1)

int main(int argc, char *argv[argc]) {
  if(argc != 2) {
    fprintf(stderr, "Format: countletters <words file>\n");
    return EXIT_FAILURE;
  }

  FILE *stream = fopen(argv[1], "r");
  if(!stream) {
    fprintf(stderr, "Failed to read words file\n");
    return EXIT_FAILURE;
  }

  int counts[ALPHABET_LENGTH] = {};
  char c;
  while((c = fgetc(stream)) != EOF) {
    if(isalpha(c))
      counts[toupper(c) - 'A']++;
  }

  int total = 0;
  for(int i = 0; i < ALPHABET_LENGTH; i++)
    total += counts[i];

  int lineCount = 0;
  constexpr int lineLimit = 4;
  for(int i = 0; i < ALPHABET_LENGTH; i++) {
    int highestIdx = 0;
    for(int j = 0; j < ALPHABET_LENGTH; j++)
      if(counts[j] > counts[highestIdx])
        highestIdx = j;

    if(counts[highestIdx]) {
      printf("%c: %i (%.2f%)", highestIdx + 'A', counts[highestIdx],
             (float)counts[highestIdx] / (float)total * 100.0);
      if(++lineCount >= lineLimit || i + 1 >= ALPHABET_LENGTH) {
        printf("\n");
        lineCount = 0;
      } else
        printf("\t");
    }
    counts[highestIdx] = -1;
  }

  return EXIT_SUCCESS;
}

