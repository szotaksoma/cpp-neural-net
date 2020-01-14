CC = g++
INC = -I ./include
OCFLAGS = -Wall -c

console_test: clean console_test.o console.o
	$(CC) $(INC) obj/console_test.o obj/console.o -o bin/console_test

console_test.o: src/test/console_test.cpp
	$(CC) $(INC) $(OCFLAGS) src/test/console_test.cpp -o obj/console_test.o

console.o: src/util/console.cpp
	$(CC) $(INC) $(OCFLAGS) src/util/console.cpp -o obj/console.o

# test: main.o activations.o
# 	g++ $(INC) obj/main.o obj/activations.o -o bin/test

# main.o: src/main.cpp
# 	g++ $(INC) $(OCFLAGS) src/main.cpp -o obj/main.o

# activations.o: src/activations.cpp
# 	g++ $(INC) $(OCFLAGS) src/activations.cpp -o obj/activations.o

clean:
	rm -f obj/*.o bin/*