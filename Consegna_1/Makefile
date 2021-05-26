CFLAGS = -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h Makefile

all: bin/generic_array bin/generic_array_tests

run: bin/generic_array
	bin/generic_array records.csv ./ $(K)

tests: bin/generic_array_tests
	bin/generic_array_tests

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/generic_array: build/generic_array.o build/generic_array_main.o $(COMMON_DEPS)
	$(CC) -o bin/generic_array build/generic_array.o build/generic_array_main.o

bin/generic_array_tests: build/generic_array_tests.o build/generic_array.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/generic_array_tests build/generic_array_tests.o build/generic_array.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/*