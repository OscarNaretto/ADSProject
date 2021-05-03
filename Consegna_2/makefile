CFLAGS = -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h Makefile


all: bin/edit_distance_main

run: bin/edit_distance_main
	bin/edit_distance_main correctme.txt dictionary.txt

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

bin/edit_distance_main: build/edit_distance_lib.o build/edit_distance_main.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_main build/edit_distance_lib.o build/edit_distance_main.o

clean:
	$(RM) build/*
	$(RM) bin/*