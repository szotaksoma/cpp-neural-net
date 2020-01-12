INC = -I ./include
OCFLAGS = -Wall -c

test: main.o activations.o
	g++ $(INC) obj/main.o obj/activations.o -o bin/test

main.o: src/main.cpp
	g++ $(INC) $(OCFLAGS) src/main.cpp -o obj/main.o

activations.o: src/activations.cpp
	g++ $(INC) $(OCFLAGS) src/activations.cpp -o obj/activations.o

clean:
	rm -f obj/*.o bin/*