#include "undecline.h"

using namespace std;

string Undecliner::undecline(string arg)
{
	cout << "You asked me to undecline " << arg << "\n";
	for	(int i = 0; i < NUMBER_OF_ENDINGS; i++)
	{
		if(endsWith(arg, nounEndings[i]))
		{
			string descriptor = "Declension " + std::to_string((i / 36) + 1) + " "; //Find the declension
			descriptor += i % 36 > 17 ? "Plural " : "Singular "; //If it's more than halfway through its declension, it's plural
			switch((i % 36) / 6)
			{
				case 0:
				case 3:
					descriptor += "Masculine ";
					break;
				case 1:
				case 4:
					descriptor += "Feminine ";
					break;
				case 2:
				case 5:
					descriptor += "Neuter ";
					break;
				default:
					std::cout << "Something went horribly wrong with the noun parser.  You should probably see a doctor.\n";
			}
			descriptor += "noun in the ";

			switch(i % 6) //Find the case
			{
				case 0:
					descriptor += "nominative ";
					break;
				case 1:
					descriptor += "genitive ";
					break;
				case 2:
					descriptor += "dative ";
					break;
				case 3:
					descriptor += "accusative ";
					break;
				case 4:
					descriptor += "ablative ";
					break;
				case 5:
					descriptor += "vocative ";
					break;
				default:
					std::cout << "Something went horribly wrong with the noun parser.  You should probably see a doctor.\n";
			}
			descriptor += "case\n";

			std::cout << "Found matching ending: " << nounEndings[i] << " for a " << descriptor; 
		}
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
