#include <iostream>
#include <string>
#include <vector>
#include<fstream> 
#include<iomanip>
#include <cassert>

#include<tuple>

//global using directives: 
using std::cout; 
using std::cin; 
using std::endl; 

using std::string;
using std::vector;

using std::ofstream;
using std::ifstream; 

using std::setw; 
using std::left; 


/*"inefficient" because string.erase method potentially SHIFTS "many" chars*/
void removeConsecutiveDuplicates_inefficientApproach(string& s)
{
	//string resultWithoutDuplicates; 

	for (int i = 0; i < s.length() - 1; ) 
		//note the -1 
		// NOTE!! the lack of increment!
	{
		if (s[i] == s[i + 1])
		{
			s.erase(i + 1, 1); 
		}

		else
		{
			i++; 
		}
	}
}

string removeConsecutiveDuplicates(string& s)
{
	assert(s.length() > 1); 


	string result; 

	result += s[0]; 

	for (int i = 1; i < s.length(); i++)
	{
		if (s[i] != result.back())
		{
			result += s[i]; 
		}
	}

	return result; 

}

/*Replaces 2nd through last char with hyphen if a, e, i, o, u, y, h, or w
interesting examples of the last two consonants:
honor - h is silent 
whip - h is silent (unless Stewy Griffin)
yellow - hello yello yellow (weird English rules)
answer - anser (madness)
*/
void hyphenateVowelsAndSpecificConsonants(string& s)
{
	for (int i = 1; i < s.length(); i++)
	{
		char currentLetter = s[i]; 

		switch (currentLetter)
		{

		case 'a': 
		case 'e': 
		case 'i': 
		case 'o': 
		case 'u': 
		case 'y': 
		case 'h': 
		case 'w': 
			s[i] = '-';
			break; 

		default: 
			//no change
			break; 
		}
	}
}

void replaceOtherLettersWithNumbers(string& s)
{
	for (int i = 1; i < s.length(); i++)
	{
		char currentLetter = s[i];

		switch (currentLetter)
		{
		case 'b': 
		case 'f': 
		case 'p': 
		case 'v': 
			s[i] = '1'; 
			break; 

		case 'c':
		case 'g': 
		case 'j': 
		case 'k': 
		case 'q': 
		case 's':
		case 'x': 
		case 'z': 
			s[i] = '2'; 
			break; 

		case 'd': 
		case 't': 
			s[i] = '3'; 
			break; 

		case 'l': 
			s[i] = '4'; 
			break;

		case 'm': 
		case 'n': 
			s[i] = '5'; 
			break; 

		case 'r': 
			s[i] = '6'; 
			break;

		default: 
			//no change
			break; 
		}
	}


}

string deleteHyphens(string& s)
{
	string result; 
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != '-') //NOT equal
		{
			result += s[i]; 
		}
	}

	return result; 
}

string calcSoundexCode(string& originalString)
{
	
	//"Step 1" (remove adjacent duplicates (or triplicates?) - 
	//ex: jolly becomes joly 
	//removeConsecutiveDuplicates_inefficientApproach(originalString); 
	removeConsecutiveDuplicates(originalString); 


	//Step 2
	hyphenateVowelsAndSpecificConsonants(originalString); 

	//Step 3
	replaceOtherLettersWithNumbers(originalString); 

	//Step 4
	originalString = deleteHyphens(originalString); 

	originalString = originalString.substr(0, 4); 

	string soundexCode = originalString; 

	return soundexCode; 


}

void demoSoundexAlgo(vector<std::pair<string, string>> stringPairs)
{
	for (auto& pair : stringPairs)
	{
		string firstString = pair.first; 
		string secondString = pair.second; 

		cout << "First string: " << firstString; 

		cout << " has Soundex code = " << calcSoundexCode(firstString) 
			<< "\n";

		cout << "Second string: " << secondString;

		cout << " has Soundex code = " << calcSoundexCode(secondString)
			<< "\n";
	}
}



int main()
{
	vector<std::pair<string, string>> stringPairs; 

	
	stringPairs.push_back({ "Robert", "Rupert" });
	stringPairs.push_back({ "Steven", "Stephen" });

	demoSoundexAlgo(stringPairs); 

	cout << "\n\nTesting triplet of strings now ...\n";

	std::tuple<string, string, string> stringTriplet
		{"Catherine", "Katherine", "Cathryn"};

	//for (int i = 0; i < stringTriplet)
	cout << std::get<0>(stringTriplet); 
	cout << " has Soundex code = " << calcSoundexCode(std::get<0>(stringTriplet))
		<< "\n";

	cout << std::get<1>(stringTriplet);
	cout << " has Soundex code = " << calcSoundexCode(std::get<1>(stringTriplet))
		<< "\n";

	cout << std::get<2>(stringTriplet);
	cout << " has Soundex code = " << calcSoundexCode(std::get<2>(stringTriplet))
		<< "\n";


	//string s1 = "extenssions"; 
	

	//cout << s1 << " has Soundex code: "; 
	
	//calcSoundexCode(s1); 

	//cout << s1 <<  "\n";

	return 0; 
}