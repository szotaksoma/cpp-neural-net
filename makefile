# Compiler
CC = g++
# Include paths
INC = -I./include
# Compilation flags
CFLAGS = -Wall -c -g

# Tests

model_test: src/test/model_test.cpp NeuralNet.a
	$(CC) $(INC) $(CFLAGS) $< -o bin/$@.o && \
	$(CC) bin/$@.o -Lbin/static -l:NeuralNet.a -o bin/$@ && \
	make clean-o && \
	$(call success,"Build successful!")

# Library

NeuralNet.a: activations.o layers.o model.o data.o args.o debug.o errors.o
	cd bin/static && ar rcs $@ $^; cd ../.. && make clean-o

# Modules

activations.o: src/core/activations.cpp include/core/activations.h
	$(CC) $(INC) $(CFLAGS) $< -o bin/static/$@

layers.o: src/core/layers.cpp include/core/layers.h
	$(CC) $(INC) $(CFLAGS) $< -o bin/static/$@

model.o: src/core/model.cpp include/core/model.h
	$(CC) $(INC) $(CFLAGS) $< -o bin/static/$@

data.o: include/core/data.h
	$(CC) $(INC) $(CFLAGS) $< -o bin/static/$@

args.o: src/util/args.cpp include/util/args.h
	$(CC) $(INC) $(CFLAGS) $< -o bin/static/$@

debug.o: src/util/debug.cpp include/util/debug.h
	$(CC) $(INC) $(CFLAGS) $< -o bin/static/$@

errors.o: src/util/errors.cpp include/util/errors.h
	$(CC) $(INC) $(CFLAGS) $< -o bin/static/$@

clean-o:
	@echo "Cleaning module binaries"
	rm -f bin/static/*.o bin/*.o

clean:
	@echo "Cleaning all binaries"
	rm -rf bin/static
	rm -f bin/*
	mkdir bin/static

define memcheck
	valgrind bin/$1
endef

define success
	echo "\e[1m$1\e[0m"
endef
