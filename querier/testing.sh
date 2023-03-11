#!/bin/bash


# Insufficient
./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 



# Too many arguments
./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index ball


# Invalid pageDirectory
./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-99 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index



#invalid indexfile
#./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 Invalid



echo "and" | ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index


echo "or" | ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index

echo "Dartmouth or and COLLEGE" | ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index



# VALID QUERY INPUT

echo " DARTMOUTH or COLLEGE" | ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/toscrape-2 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/toscrape-2.index

echo " computers or science or lab sky " | ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/toscrape-2 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/toscrape-2.index



./fuzzquery /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index 10 1 | ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index


./fuzzquery /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/toscrape-2.index 10 1 | ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/toscrape-2 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/toscrape-2.index


./fuzzquery /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index 10 1 | valgrind ./querier /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10 /thayerfs/home/f004pkp/cs50-dev/shared/tse/output/letters-10.index





