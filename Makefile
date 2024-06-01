all: help

FLAGS+=-Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual

build:
	gcc src/*.c src/**/*.c -c -O3 $(FLAGS)
	make post
	
debug:
	gcc src/*.c src/**/*.c -c -g $(FLAGS) -DLOG_DEBUG
	make post

post:
	ar rcs liblibyfy.a *.o
	rm src/**/*.gch -rf

run: debug
run:
	gcc main.c -o main -L. -Isrc -llibyfy -g $(FLAGS) -fsanitize=address,undefined
	./main

test: debug
test:
	gcc tests/*.c tests/**/*.c -o "tests/tests" -L. -Isrc -llibyfy -g $(FLAGS) -fsanitize=address,undefined -DLOG_DEBUG 
	./tests/tests

clean:
	rm *.o *.a -rf
	rm src/**/*.gch -rf
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