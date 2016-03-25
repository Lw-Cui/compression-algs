CC		= icc
CXXFLAG	= -g -O0 -Wall -Wextra -W -std=c++11 

all			: Huffman.out

Huffman.out	: Huffman.o
	$(CC) $(CXXFLAG) $< -o $@ 

Huffman.o	: Huffman.cpp
	$(CC) $(CXXFLAG) $< -o $@ -c

clean:
	rm *.o *.out

rebuild: clean all
	
.PHONY: all clean rebuild
