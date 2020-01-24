# Compiler
CC = g++
# Include paths
INC = -I ./include
# Compilation flags
OCFLAGS = -Wall -c

##### Executables #####

model_test: model_test_o model_o layers_o activations_o debug_o errors_o
	$(CC) $(INC) -g obj/model_test.o obj/model.o obj/layers.o obj/activations.o obj/debug.o obj/errors.o -o bin/model_test

activations_test: activations_test_o activations_o
	$(CC) $(INC) -g obj/activations_test.o obj/activations.o -o bin/activations_test

debug_test: debug_test_o debug_o args_o
	$(CC) $(INC) -g obj/debug_test.o obj/args.o obj/debug.o -o bin/debug_test

data_test: data_test_o debug_o errors_o
	$(CC) $(INC) -g obj/data_test.o obj/debug.o obj/errors.o -o bin/data_test

##### Other targets #####

memcheck_model_test: model_test
	$(call memcheck,model_test)
	make clean

##### Test objects #####

activations_test_o: src/test/activations_test.cpp
	$(call compile,test,activations_test)

model_test_o: src/test/model_test.cpp
	$(call compile,test,model_test)
	
debug_test_o: src/test/debug_test.cpp
	$(call compile,test,debug_test)

data_test_o: src/test/data_test.cpp
	$(call compile,test,data_test)

##### Core objects #####

activations_o: src/core/activations.cpp
	$(call compile,core,activations)

layers_o: src/core/layers.cpp
	$(call compile,core,layers)

model_o: src/core/model.cpp
	$(call compile,core,model)

args_o: src/util/args.cpp
	$(call compile,util,args)

##### Util objects #####

debug_o: src/util/debug.cpp
	$(call compile,util,debug)

errors_o: src/util/errors.cpp
	$(call compile,util,errors)

##### Other targets and helper functions #####

clean:
	rm -f obj/*.o bin/*

# Usage: $1 -> group [core|util|test], $2 -> unit name (no extension)
define compile
	$(CC) $(INC) $(OCFLAGS) src/$1/$2.cpp -o obj/$2.o
endef

define memcheck
	valgrind bin/$1
endef
