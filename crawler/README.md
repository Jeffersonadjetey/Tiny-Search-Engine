#cs50 Lab 4
### cs50 Winter 2022


### crawler
A crawler crawls a website and retrieve webpages beginning with a given URL. 


### Usage

The crawler method uses the functions below:

```c
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
```

### Implementation

Please refer to IMPLEMENTATION.md for information about implementation




### Assumptions

No assumptions as I used the same assumptions listed.


(note: After running, I seem to be missing the '1' file in every subdirectory. Everything else matches the example already given. Also I'm not sure but my files are available in the terminal but not in testing.out).

I have committed a print out of my data directory structure in data.out

### Files
crawler.c 
crawler.h
testing.sh
testing.out
Makefile

(note: The other specs were provided)


### Compilation
To compile, simply make crawler.o



### Testing

The testing.sh tests crawler on files and test cases.

To test, simply make test


