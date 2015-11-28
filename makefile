JAVA := $(wildcard *.java)
CLASS := $(patsubst %.java, %.class, $(JAVA))

CC := javac-algs

all: $(CLASS)

$(CLASS): %.class: %.java
	$(CC) $^

clean:
	rm $(CLASS)

rebuild: clean all
	
.PHONY: all clean rebuild
