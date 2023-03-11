#!/bin/bash

# Jefferson Adjetey/Winter, 2022

#Wrong text cases
echo "Insufficient arguments"
./crawler

echo "Too many arguments"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters ../ball/ 0


echo "Not internal"
./crawler https://en.wikipedia.org/wiki/Main_Page ../data/letters 2


echo "invalid seed URL"
./crawler http://www.Welcometocs50.edu/cs50 ../data/letters 0


echo "Invalid page directory"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../numbers/ 11


echo "Invalid depth (negative)"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters -1


echo "Invalid depth (greater than 10)"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 15







echo "Test case with valgrind"
#valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 0

echo "Test case with full valgrind"
#valgrind --leak-check=full --show-leak-kinds=all ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 0



echo "Letters at depths 0"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters-0 0


echo "Letters at depths 10"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters-10 10



echo "toscrape at depths 0"
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../data/toscrape-0 0


echo "toscrape at depth 1"
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../data/toscrape-1 1




echo "wikipedia at depth 0"
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../data/wikipedia-0 0


echo "wikipedia at depth 1"
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../data/wikipedia-1 1




