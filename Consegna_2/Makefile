CC=gcc
CFLAGS = -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h Makefile

all: bin/app_main bin/tests_run

run: bin/app_main
	bin/app_main correctme.txt dictionary.txt corrections.txt 30

test: bin/tests_run 
	bin/tests_run 

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

bin/app_main: build/edit_distance_lib.o build/dictionary.o build/app_main.o $(COMMON_DEPS)
	$(CC) -o bin/app_main build/edit_distance_lib.o build/dictionary.o build/app_main.o

bin/tests_run: build/edit_distance_lib.o build/tests_run.o build/unity.o build/dictionary.o $(COMMON_DEPS)
	$(CC) -o bin/tests_run build/edit_distance_lib.o build/tests_run.o build/unity.o build/dictionary.o

clean:
	$(RM) build/*
	$(RM) bin/*
