CC=gcc
CFLAGS = -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h Makefile

all: bin/edit_distance_main bin/edit_distance_test bin/dictionary_test

run: bin/edit_distance_main
	bin/edit_distance_main correctme.txt dictionary.txt

tests: bin/edit_distance_test bin/dictionary_test
	bin/edit_distance_test bin/dictionary_test

dict: bin/dictionary_test
	bin/dictionary_test

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

bin/edit_distance_main: build/edit_distance_lib.o build/dictionary.o build/edit_distance_main.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_main build/edit_distance_lib.o build/dictionary.o build/edit_distance_main.o

bin/edit_distance_test: build/edit_distance_lib.o build/edit_distance_test.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_test build/edit_distance_test.o build/unity.o

bin/dictionary_test: build/dictionary_test.o build/dictionary.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/dictionary_test build/dictionary_test.o build/dictionary.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/*
