CC = icc -std=c++11 
CXXFLAG	= -g -O0 -Wall -Wextra -W -I.

LIBDIR = lib
TESTDIR = test
SRCDIR	= huffmanSrc
BUILDDIR = build
HEADERDIR = huffmanHeader

HEADER = $(wildcard $(HEADERDIR)/*.hpp)
SRC = $(wildcard $(SRCDIR)/*.cpp)
SRC_OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TEST = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJ = $(TEST:$(TESTDIR)/%.cpp=$(BUILDDIR)/%.o)
LIB_A = $(wildcard $(LIBDIR)/*.a)

huffman: $(TEST_OBJ) $(SRC_OBJ) $(LIB_A)
	$(CC) $(CXXFLAG) $^ -o $@ 

$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp $(HEADER)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CXXFLAG) $< -o $@ -c

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADER)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CXXFLAG) $< -o $@ -c

clean:
	rm -rf $(BUILDDIR) 

rebuild: clean all
