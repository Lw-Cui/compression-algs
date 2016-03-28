CC = icc -std=c++11 
CXXFLAG	= -g -O0 -Wall -Wextra -W -I.

LIBDIR = lib
TESTDIR = test
SRCDIR	= huffmanSrc
BUILDDIR = build
HEADERDIR = huffmanHeader
BITHEADER = bitheader
BITDIR = bitsrc
QHEADER = qheader

HEADER = $(wildcard $(HEADERDIR)/*.hpp)\
								  $(wildcard $(BITHEADER)/*.hpp)\
								  $(wildcard $(QHEADER)/*.hpp)

LIB = $(wildcard $(LIBDIR)/*.a)
								  
SRC = $(wildcard $(SRCDIR)/*.cpp)
SRC_OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

TEST = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJ = $(TEST:$(TESTDIR)/%.cpp=$(BUILDDIR)/%.o)

BITSRC = $(wildcard $(BITDIR)/*.cpp)
BIT_OBJ = $(BITSRC:$(BITDIR)/%.cpp=$(BUILDDIR)/%.o)

huffman: $(TEST_OBJ) $(SRC_OBJ) $(BIT_OBJ) $(LIB)
	$(CC) $(CXXFLAG) $^ -o $@ 

$(BUILDDIR)/%.o: $(BITDIR)/%.cpp $(HEADER)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CXXFLAG) $< -o $@ -c

$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp $(HEADER)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CXXFLAG) $< -o $@ -c

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADER)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CXXFLAG) $< -o $@ -c

clean:
	rm -rf $(BUILDDIR) 

rebuild: clean huffman
