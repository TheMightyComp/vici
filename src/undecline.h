#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

class Undecliner
{
	public:
		void undecline(string);
		void loadEndings();
		string findNoun(string, int);

	private:
		const static int NUMBER_OF_ENDINGS = 180;
		string nounEndings[NUMBER_OF_ENDINGS];
		bool endsWith(string, string);
};
