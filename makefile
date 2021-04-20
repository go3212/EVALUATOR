CC=g++
CC_OPTS:=-O3
SRCS:=$(wildcard cpp/*.cc)
HEADERS:=$(wildcard hh/*.hh)


OBJECTS:=$(patsubst cpp/%.cc,bin/%.o,$(SRCS))



evaluator: $(OBJECTS)
	$(CC) main.cc $^ $(CC_OPTS) -o $@

bin/%.o: cpp/%.cc $(HEADERS)
	$(CC) $< $(CC_OPTS) -c -o $@

