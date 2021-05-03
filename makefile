CC=g++
#CC_OPTS:=-D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
CC_OPTS:=
SRCS:=$(wildcard cpp/*.cc)
HEADERS:=$(wildcard hh/*.hh)


OBJECTS:=$(patsubst cpp/%.cc,bin/%.o,$(SRCS))

program.exe: $(OBJECTS)
	$(CC) program.cc $^ $(CC_OPTS) -o $@

bin/%.o: cpp/%.cc $(HEADERS)
	$(CC) $< $(CC_OPTS) -c -o $@

