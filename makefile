CC=g++
#CC_OPTS:=-D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
CC_OPTS:= -O3
#CC_OPTS:= -O2
SRCS:=$(wildcard src/*.cc)
HEADERS:=$(wildcard src/*.hh)


OBJECTS:=$(patsubst src/%.cc,bin/%.o,$(SRCS))

program.exe: $(OBJECTS)
	$(CC) program.cc $^ $(CC_OPTS) -o $@

bin/%.o: src/%.cc $(HEADERS)
	$(CC) $< $(CC_OPTS) -c -o $@
