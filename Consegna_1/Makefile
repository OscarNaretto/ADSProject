CFLAGS = -g -O1 -Wall -Wextra -Wpedantic
COMMON_DEPS = src/*.h Makefile

all: bin/ordered_array bin/ordered_array_tests

order: bin/ordered_array
	bin/ordered_array $(path)

tests: bin/ordered_array_tests
	bin/ordered_array_tests

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/ordered_array: build/ordered_array.o build/ordered_array_main.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array build/ordered_array.o build/ordered_array_main.o

bin/ordered_array_tests: build/ordered_array_tests.o build/ordered_array.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array_tests build/ordered_array_tests.o build/ordered_array.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/*
	$(RM) ordered.csv
