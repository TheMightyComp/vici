
undecline: ./build ./build/main.o ./build/undecline.o ./build/dict ./build/dict/N.dict ./build/dict/DICT.txt
	g++ -std=c++11 ./build/main.o ./build/undecline.o -o ./build/undecline

./build/main.o: ./src/main.cpp
	g++ -c -std=c++11 ./src/main.cpp -o ./build/main.o

./build/undecline.o: ./src/undecline.cpp ./src/undecline.h
	g++ -c -std=c++11 ./src/undecline.cpp -o ./build/undecline.o

./build/dict/N.dict: ./dict/N.dict
	cp ./dict/N.dict ./build/dict/N.dict

./build/dict/DICT.txt: ./dict/DICT.txt
	cp ./dict/DICT.txt ./build/dict/DICT.txt

./build:
	mkdir build

./build/dict:
	mkdir ./build/dict

clean:
	rm ./build/*o
