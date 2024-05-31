all: help

FLAGS=-Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual
DEBUG_FLAGS=$(FLAGS) -g

build:
	gcc src/*.c src/*.h -c -O3 $(FLAGS)
	make post
	
debug:
	gcc src/*.c src/*.h -c -g $(DEBUG_FLAGS) -DLOG_DEBUG
	make post

post:
	ar rcs liblibify.a *.o
	rm src/*.gch

run: debug
run:
	gcc main.c -o main -L. -Isrc -llibify -g $(DEBUG_FLAGS) -fsanitize=address,undefined
	./main

test: debug
test:
	gcc tests/*.c -o "tests/tests" -L. -Isrc -llibify -g $(DEBUG_FLAGS) -fsanitize=address,undefined -DLOG_DEBUG 
	./tests/tests

clean:
	rm *.o *.a -rf
	rm src/*.gch -rf
	rm main -rf

help:
	@echo "build: build the library"
	@echo "debug: build the library with debug flags"
	@echo "run: build and run the main program"
	@echo "test: build and run the tests"
	@echo "clean: clean the project"
	@echo "help: show this message"
	@echo ""
	@echo "use CC=-DLOG_DEBUG or CC=-DLOG_TRACE to enable debug or trace logs"