# Compiler
CC = g++
# Include paths
INC = -I./include
# Compilation flags
CFLAGS = -Wall -c -g

# Tests

data_test: src/test/data_test.cpp NeuralNet.a
	@$(CC) $(INC) $(CFLAGS) $< -o bin/$@.o && \
	$(CC) bin/$@.o -Lbin/static -l:NeuralNet.a -o bin/$@ && \
	$(call success,"Build successful!")

model_test: src/test/model_test.cpp NeuralNet.a
	@$(CC) $(INC) $(CFLAGS) $< -o bin/$@.o && \
	$(CC) bin/$@.o -Lbin/static -l:NeuralNet.a -o bin/$@ && \
	$(call success,"Build successful!")

debug_test: src/test/debug_test.cpp NeuralNet.a
	@$(CC) $(INC) $(CFLAGS) $< -o bin/$@.o && \
	$(CC) bin/$@.o -Lbin/static -l:NeuralNet.a -o bin/$@ && \
	$(call success,"Build successful!")

# Library

NeuralNet.a: activations.o layers.o model.o data.o args.o debug.o errors.o
	@echo "\e[33mPacking library ($@)\e[0m"; \
	cd bin/static && ar rcs $@ $^; cd ../..

# Modules

activations.o: src/core/activations.cpp include/core/activations.h
	@$(call diff_compile,$@,$<)

layers.o: src/core/layers.cpp include/core/layers.h
	@$(call diff_compile,$@,$<)

model.o: src/core/model.cpp include/core/model.h
	@$(call diff_compile,$@,$<)

data.o: src/core/data.cpp include/core/data.h
	@$(call diff_compile,$@,$<)

args.o: src/util/args.cpp include/util/args.h
	@$(call diff_compile,$@,$<)

debug.o: src/util/debug.cpp include/util/debug.h
	@$(call diff_compile,$@,$<)

errors.o: src/util/errors.cpp include/util/errors.h
	@$(call diff_compile,$@,$<)

clean-o:
	@echo "Cleaning module binaries"
	rm -f bin/static/*.o bin/*.o

clean:
	@echo "Cleaning all binaries" \
	&& rm -rf bin/static && rm -f bin/* && mkdir bin/static

dirs:
	@mkdir \
	diff \
	diff/src \
	diff/src/core \
	diff/src/test \
	diff/src/util \
	bin \
	bin/static \

define diff_compile
	[ ! -s bin/static/$1 -o ! -s diff/$2 -o "`diff $2 diff/$2`" ] \
	  && (echo "\e[33mCompiling $2\e[0m" \
	  && cp $2 diff/$2 \
	  && $(CC) $(INC) $(CFLAGS) $2 -o bin/static/$1) \
	|| echo "\e[37mSkipping $2 (up to date)\e[0m"
endef

define success
	echo "\e[32;1m$1\e[0m"
endef
