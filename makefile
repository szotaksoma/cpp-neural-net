CC = g++
INC = -I ./include
OCFLAGS = -Wall -c

##### Executables #####

activations_test: activations_test_o activations_o
	$(CC) $(INC) obj/activations_test.o obj/activations.o -o bin/activations_test

console_test: console_test_o console_o
	$(CC) $(INC) obj/console_test.o obj/console.o -o bin/console_test

##### Test objects #####

activations_test_o: src/test/activations_test.cpp
	$(call compile,test,activations_test)

model_test_o: src/test/model_test.cpp
	$(call compile,test,model_test)
	
console_test_o: src/test/console_test.cpp
	$(call compile,test,console_test)

##### Core objects #####

activations_o: src/core/activations.cpp
	$(call compile,core,activations)

layers_o: src/core/layers.cpp
	$(call compile,core,layers)

model_o: src/core/model.cpp
	$(call compile,core,model)

##### Util objectss #####

console_o: src/util/console.cpp
	$(call compile,util,console)

errors_o: src/util/errors.cpp
	$(call compile,util,errors)

##### Other targets and helper functions #####

clean:
	rm -f obj/*.o bin/*

# Usage: $1 -> group [core|util|test], $2 -> unit name (no extension)
define compile
	$(CC) $(INC) $(OCFLAGS) src/$1/$2.cpp -o obj/$2.o
endef
