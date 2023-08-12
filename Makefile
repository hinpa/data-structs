CC=clang

CFLAGS=-g -Wall
LINKER_FLAGS=-lstdc++
LIBS=src
CODEDIRS=. $(foreach D,$(LIBS), $(wildcard $(D)/*))
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
BINARY=bin

all:$(BINARY)

$(BINARY):$(OBJECTS)
	$(CC) $(LINKER_FLAGS) $(CFLAGS) $^ -o $@

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJECTS) $(BINARY)
