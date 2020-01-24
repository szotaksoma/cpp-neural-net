# Compiler
CC = g++
# Include paths
INC = -I ./include
# Compilation flags
CFLAGS = -Wall -c -g

# Tests

model_test: src/test/model_test.cpp NeuralNet.a
	$(CC) $(INC) $(CFLAGS) $< -o obj/$@.o && \
	$(CC) obj/$@.o lib/NeuralNet.a -o bin/$@

# Library

NeuralNet.a: activations.o layers.o model.o data.o args.o debug.o errors.o
	cd lib && ar rcs $@ $^; cd ..

# Modules

activations.o: src/core/activations.cpp include/core/activations.h
	$(CC) $(INC) $(CFLAGS) $< -o lib/$@

layers.o: src/core/layers.cpp include/core/layers.h
	$(CC) $(INC) $(CFLAGS) $< -o lib/$@

model.o: src/core/model.cpp include/core/model.h
	$(CC) $(INC) $(CFLAGS) $< -o lib/$@

data.o: include/core/data.h
	$(CC) $(INC) $(CFLAGS) $< -o lib/$@

args.o: src/util/args.cpp include/util/args.h
	$(CC) $(INC) $(CFLAGS) $< -o lib/$@

debug.o: src/util/debug.cpp include/util/debug.h
	$(CC) $(INC) $(CFLAGS) $< -o lib/$@

errors.o: src/util/errors.cpp include/util/errors.h
	$(CC) $(INC) $(CFLAGS) $< -o lib/$@

clean:
	rm -f obj/* bin/* lib/*

# Usage: $1 -> group [core|util|test], $2 -> unit name (no extension)
define compile
	$(CC) $(INC) $(CFLAGS) src/$1/$2.cpp -o obj/$2.o
endef

define memcheck
	valgrind bin/$1
endef
