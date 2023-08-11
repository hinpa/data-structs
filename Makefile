CC=gcc

CFLAGS=-g -Wall -lm
LIBS=src
CODEDIRS=. $(foreach D,$(LIBS), $(wildcard $(D)/*))
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
BINARY=bin

all:$(BINARY)

$(BINARY):$(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJECTS) $(BINARY)
