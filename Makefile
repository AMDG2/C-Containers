CC = gcc

all: examples

examples: list stack queue map

list: examples/list/main.c src/list.h src/helpers.h
	${CC} examples/list/main.c -o examples/list/pile

stack: examples/stack/main.c src/stack.h src/helpers.h
	${CC} examples/stack/main.c -o examples/stack/stack

queue: examples/queue/main.c src/queue.h src/helpers.h
	${CC} examples/queue/main.c -o examples/queue/queue

map: examples/map/main.c src/map.h src/helpers.h
	${CC} examples/map/main.c -o examples/map/map

documentation: examples/%/main.c src/list.h src/map.h src/helpers.h Doxyfile
	doxygen Doxyfile
