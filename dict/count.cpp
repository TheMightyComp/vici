//Tiny program to count the number of lines
//In the dictionary file
//Just run "count" to count the lines in DICT.txt
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	ifstream inStream("DICT.txt");
	string curLine;
	int i = 0;
	while (std::getline(inStream, curLine))
		i++;

	std::cout << i << endl;
	return 0;
}
