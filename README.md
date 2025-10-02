# Using custom word lists

First, unlink the current words file
```
$ unlink words.txt
```

Then, link the words.txt to the file you want
```
$ ln -s <WORD FILE> words.txt
```

## Built in word lists

- wave1.txt: The default words list of 500 words
- dictionary.txt: All words in the english language from
  https://github.com/dwyl/english-words
- francais.txt: All words from french without diacritics. Licensed under
  the MIT license in licenses/francais_mit.txt and available at
  https://github.com/Taknok/French-Wordlist

