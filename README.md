# Changes from f030d3b
- In previous versions, streaks would reset 24 hours after the last renew.
  Now, the user has until the end of the next day (midnight UTC).

# Using custom word lists
By default, the file linked to words.txt is used
```
$ ./program <path to words file>
```

## Built in word lists

- edition1.txt: The default words list of 500 words
- dictionary.txt: All words in the english language from
  https://github.com/dwyl/english-words
- francais.txt: All words from french without diacritics. Licensed under
  the MIT license in licenses/francais_mit.txt and available at
  https://github.com/Taknok/French-Wordlist
- hyphens: All words from dictionary.txt that contain a hyphen

