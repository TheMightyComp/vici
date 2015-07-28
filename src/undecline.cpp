#include "undecline.h"

using namespace std;

string Undecliner::undecline(string arg)
{
	cout << "You asked me to undecline " << arg << "\n";
	for	(int i = 0; i < NUMBER_OF_ENDINGS; i++)
	{
		if(endsWith(arg, nounEndings[i]))
			std::cout << "Found matching ending: " << nounEndings[i] << endl;
	}
	return arg;
}

void Undecliner::loadEndings()
{
	string curLine;
	ifstream nounEndingsFile("./dict/N.dict");
	int i = 0;
	if(nounEndingsFile.is_open())
	{
		while(std::getline(nounEndingsFile, curLine))
		{
			if(curLine.front() == '#') //skip comments
				continue;
				if(curLine.front() == '-') //this is a definition we want
				{
					curLine.front() = ' ';//Get rid of the "-" in front
					std::istringstream iss(curLine); //seperates the string by spaces
						do
						{
							string sub;
							iss >> sub;
							//cout << "Substring: " << sub << endl;
							if(!sub.empty())
								nounEndings[i++]=sub; //Add each ending to the list

						} while(iss);
				}
		}
		nounEndingsFile.close();
	}
	else
		cout << "Unable to find noun endings file!" << endl;

	/* Testing code to see if everything loaded correctly
	for(int i = 0; i < NUMBER_OF_ENDINGS; i++)
	{
		std::cout << "Loaded ending " << i << ": " << nounEndings[i] << endl;
	} */
}


//Checks to see if a word ends with the given string
bool Undecliner::endsWith(string word, string ending)
{
	//Start searching from the back of each string
	std::string::reverse_iterator rWord = word.rbegin();
	std::string::reverse_iterator rEnding = ending.rbegin();
	//Until we've exhausted the characters in the ending
	while (rEnding != ending.rend())
	{
		if(*rWord != *rEnding) //If the ending and word characters differ, it didn't work
			return false;

			//Go to the next character back
			++rWord;
			++rEnding;
	}
	return true;
}
