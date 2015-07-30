#include "undecline.h"

using namespace std;

//Takes a given noun (in any case) and returns its nominative form
void Undecliner::undecline(string arg)
{
	cout << "You asked me to undecline " << arg << "\n";
	for	(int i = 0; i < NUMBER_OF_ENDINGS; i++)
	{
		if(endsWith(arg, nounEndings[i]))
		{
			int declension = (i / 36) + 1;
			string descriptor = "Declension " + std::to_string(declension) + " "; //Find the declension
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
			
			//Find possible matches from ending
			string stem = "";
			for(int j = 0; j < (int)arg.length() - (int)nounEndings[i].length(); j++) //Chop off the stem
			{
				stem += arg[j];
			}

			std::cout << "My best guess for this ending is the noun " << this->findNoun(stem, declension) << endl << endl;
		}
	}
	//return arg;
}

//Loads the known noun endings for all declensions from the file ./dict/N.dict
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

//Takes a stem and a declension, constructs a SPP, and finds the noun in the dictionary
string Undecliner::findNoun(string st, int declension)
{
	ifstream dictFile("./dict/DICT.txt");
	if(dictFile.is_open())
	{
		//std::cout << "Successfully opened file" << endl;
		string curLine;

		/*TODO: This search is HORRIBLE - it has to go through the whole dictionary alphabetically
		 * Find a way to read a given line from the file, and do a binary search
		 * Then it will be a billion times better */
		while(std::getline(dictFile, curLine))
		{
			string stem = st; //the string is passed by reference, and we can't have that
			if(curLine.front() == '#') //Confusingly, this is the line delimiter in the dictionary.  Don't blame me, I didn't make it.
			{
				curLine.front() = ' '; //Again, remove the hash because string stream doesn't like it
				std::istringstream iss(curLine);
				string w1, w2, w3; //We just have to look at the first three words - that gives us the FPP, SPP, and PoS
				iss >> w1;
				iss >> w2;
				iss >> w3;
				//cout << "w3 = " << w3 << endl;
				if(w3.front() == 'N') //If it is a noun
				{
					switch(declension)
					{
						case 1:
							stem += "ae";
							break;
						case 2:
							stem += "i";
							break;
						case 3:
							stem += "is";
							break;
						case 4:
							stem += "us";
							break;
						case 5:
							stem += "ei";
							break;
						default:
							std::cout << "Something went horribly wrong: Declension " << declension << " does not exist!" << endl;

					}	
				}
				else
					continue;

				//I don't know if there's a string::equals(), so I wrote my own.
				std::string::iterator iS = stem.begin();
				std::string::iterator dS = w2.begin();
				bool foundMatch = true;
				while(iS != stem.end() && dS != w2.end())
				{
					if(*iS != *dS)
					{	
						foundMatch = false;
						break;
					}	
					++iS;
					++dS;
				}

				if(foundMatch && iS == stem.end() && dS == w2.end()) //Last two conditionals ensure that stem is not a subset of w2 or vice versa
				{
					dictFile.close();
					//cout << "Determined that stem -" << stem << "- is equal to 2PP -" << w2 << "-" << endl;
					return w1;
				}
		    	/*else
					cout << "Determined that stem -" << stem << "- is not equal to 2PP -" << w2 << "-" << endl; */

			}
		}	
	}
	else
		std::cout << "Did not successfully open file." << endl;
		

	dictFile.close();
	return "Did not find any matching nouns for " + st + "!";
}
