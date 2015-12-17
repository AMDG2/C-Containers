CC = gcc

FLAGS = -Wall -ggdb

all: examples

examples: list stack queue map set

list: examples/list/main.c src/list.h src/helpers.h
	${CC} ${FLAGS} src/helpers.h examples/list/main.c -o examples/list/list

stack: examples/stack/main.c src/stack.h src/helpers.h
	${CC} ${FLAGS} src/helpers.h examples/stack/main.c -o examples/stack/stack

queue: examples/queue/main.c src/queue.h src/helpers.h
	${CC} ${FLAGS} src/helpers.h examples/queue/main.c -o examples/queue/queue

map: examples/map/main.c src/map.h src/helpers.h
	${CC} ${FLAGS} src/helpers.h examples/map/main.c -o examples/map/map

set: examples/set/main.c src/set.h src/helpers.h
	${CC} ${FLAGS} src/helpers.h examples/set/main.c -o examples/set/set

clean: 
	rm examples/list/list
	rm examples/stack/stack
	rm examples/queue/queue
	rm examples/map/map
	rm examples/set/set

documentation: examples/%/main.c src/list.h src/map.h src/helpers.h Doxyfile
	doxygen Doxyfile
