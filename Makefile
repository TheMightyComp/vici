undecline: ./build ./build/main.o ./build/undecline.o
	g++ ./build/main.o ./build/undecline.o -o ./build/undecline

./build/main.o: ./src/main.cpp
	g++ -c ./src/main.cpp -o ./build/main.o

./build/undecline.o: ./src/undecline.cpp ./src/undecline.h
	g++ -c ./src/undecline.cpp -o ./build/undecline.o

./build:
	mkdir build

clean:
	rm ./build/*o
