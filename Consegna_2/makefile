CFLAGS = -g -O1 -Wall -Wextra -Wpedantic -Wconversion

all: bin/edit_distance_main

run: bin/edit_distance_main
	bin/edit_distance_main $(text) $(dct)

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS) 

bin/edit_distance_main: build/edit_distance_main.o
	$(CC) -o bin/edit_distance_main build/edit_distance_main.o

clean:
	$(RM) build/*
	$(RM) bin/*