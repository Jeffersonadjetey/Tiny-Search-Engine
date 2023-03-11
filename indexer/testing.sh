#!/bin/bash

# Jefferson Adjetey



echo "no arguments"
./indexer


echo "one argument"
./indexer ../data-test/wikipedia-1

echo "three or more argument"
./indexer ../data/letters-0 ../data/letters-0 test

echo "invalid pageDirectory(non-existent path)"
./indexer ../ball/wikipedia-1 ../data-new/wikipedia-index-1




echo "invalid indexFile (read-only directory)"

./indexer ../data/wikipedia-1 ../boy/

echo "-------------------------------------------"

echo "valid test(letters-10)"
./indexer ../data/letters-10 letters-index-10

echo "-----------------------------------------------"

echo "valid test(wikipedia-0)"
./indexer ../data/wikipedia-0 wikipedia-index-10

echo "-------------------------------------------------"

echo "valid test(wikipedia-1)"
./indexer ../data/wikipedia-1 wikipedia-index-1

echo "-------------------------------------------"

echo "valgrind"
valgrind --leak-check=full --show-leak-kinds=all ./indexer ../data/letters-0 valgrindtest






