# FindUnique: Multi-File Processor Application to Find Most Common Words

This program processes a batch of files and determines the unique content of the files by processing the top unique words with their respective count.

Created by Connor Dye as a California Polytechnic University Project.

## Features
- `readstring.c` is a custom library that reads a string of arbitrary length from a file and returns a pointer to a lowercase version of it in a buffer
- `hash.c` and hash.h is a custom hash data structure which includes a hash item struct to represent each word and its count, and a hash table where each word can be  mapped and quickly accessed
- `uniq.c` contains the parsing and main functionality
- Accepts an optional argument `-n <number of words>` which allows the user to specify number of words to display
- Utilizes `getopt()` to parse command line arguments
- Words are displayed with their count followed by the word in all lowercase
- Includes appropriate error checking for files that cannot be opened, invalid command line arguments, etc.
- Proper C memory management (`malloc()` to designate memory and `free()` for memory which is no longer being used)




