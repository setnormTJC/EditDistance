#include <iostream>
#include <string>
#include <vector>
#include<fstream> 
#include<iomanip>
#include <map>

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

std::vector<string> getDictionaryWords()
{
	vector<string> allWords;

	string filename = "25KDictionary.txt";
	std::ifstream allWordsFile{ filename };

	if (!allWordsFile)
	{
		cout << "Could not find file named: " << filename << "\n";

		return allWords; //...
	}

	string currentWord;
	while (!allWordsFile.eof())
	{
		std::getline(allWordsFile, currentWord);
		allWords.push_back(currentWord);
	}
	allWordsFile.close();
	cout << "word count: " << allWords.size() << "\n";


	return allWords;
}

int recursiveCalcLevenshteinDistance(const string& a, const string& b)
{
	//cout << "Called RECURSIVE version of Levenshtein distance algo...\n";

	if (b.length() == 0)
	{
		//cout << "Second string has length ZERO\n";
		return a.length();
	}

	if (a.length() == 0)
	{
		//cout << "First string has length ZERO\n";
		return b.length();
	}

	string tailOfA = a.substr(1, a.length());
	//cout << "Tail of first string: " << tailOfA << " and its length: " << tailOfA.length() << "\n";

	string tailOfB = b.substr(1, b.length());
	//cout << "Tail of SECOND string: " << tailOfB << " and its length: " << tailOfB.length() << "\n";


	if (a.at(0) == b.at(0))
	{
		return recursiveCalcLevenshteinDistance(tailOfA, tailOfB);
	}

	else
	{
		int minimum = 0;

		int x = recursiveCalcLevenshteinDistance(tailOfA, b);
		int y = recursiveCalcLevenshteinDistance(a, tailOfB);
		int z = recursiveCalcLevenshteinDistance(tailOfA, tailOfB);

		return 1 + std::min({ x, y, z });
	}
}

/*acts as a sort of filter to prevent an expensive number of words from having their edit distances calculated
ALSO only returns words with SAME FIRST letter (uncommon to get wrong?)*/
vector<string> getWordsWithinNChars(int N, const string& startWord, const vector<string>& allWords)
{
	vector<string> wordsWithinNChars; 

	for (auto& word : allWords)
	{

		int charCountDifference = startWord.length() - word.length();

		if ( (startWord[0] == word[0]) && abs(charCountDifference) < N) //same start char!
		{
			wordsWithinNChars.push_back(word);
		}
	}

	return wordsWithinNChars; 
}

std::multimap<int, string> mapWordsToLevenshteinDistances(const string& startWord,
	const vector<string> finishWords)
{
	//cat <- hat 
	//cat -> mat 
	std::multimap<int, string> wordsAndTheirLevenshteinDistance; 


	int counter = 0; 

	for (int i = 0; i < finishWords.size(); i++)
	{
		//for the sake of expense (and assuming no absurdly-bad misspellings), 
		//ONLY find Levenshtein distance if string lengths differ by no more than 4 chars
		
		int currentWordLevDistance = recursiveCalcLevenshteinDistance(startWord, finishWords.at(i));

			//cout << "Levenshtein distance between " << startWord << " and " << finishWords.at(i) << " is :"
			//	<< currentWordLevDistance << "\n";

		wordsAndTheirLevenshteinDistance.insert({ currentWordLevDistance, finishWords.at(i) });

		
		counter++; 

		if (counter % 10 == 0)
		{
			//cout << "Pushed " << counter << " th pair onto map " << endl; 
			//cout << "\t...containing " << finishWords.at(i) << " with edit distance = " << currentWordLevDistance << "\n";


			cout << "Top match so far ...\n";
			cout << "\t" << wordsAndTheirLevenshteinDistance.begin()->second
				<< " with an edit distance of "  << wordsAndTheirLevenshteinDistance.begin()->first << "\n";
		}
	}

	return wordsAndTheirLevenshteinDistance; 
}


int main()
{
	vector<string> allWords = getDictionaryWords(); 

	string startWord = "accommadate"; //absence

	int stringLengthDifferenceLimit = 3; //ex: misspelling "character" as "cat" will not get detected 
										//but misspelling "bat" or "cast" as cat WILL get detected (possibly) 

	vector<string> closeLengthWords = getWordsWithinNChars(stringLengthDifferenceLimit, startWord, allWords);

	
	cout << "Words with lengths within " << stringLengthDifferenceLimit << " of " << startWord << endl; 
	cout << "(" << closeLengthWords.size() << " of these exist)\n";
	for (auto& word : closeLengthWords)
	{
		cout << word << "\n";
	}

	cout << "\n\n\nAny key to continue..."; 
	cin.get(); 


	auto resultingMap = mapWordsToLevenshteinDistances(startWord, closeLengthWords);

	int desiredNumberOfNeighborsToDisplay = 10; 
	cout << startWord << " is most similar to the following " << desiredNumberOfNeighborsToDisplay << " words ...\n";
	
	auto mapIterator = resultingMap.begin(); 
	int iterationCounter = 0; 
	while(iterationCounter < desiredNumberOfNeighborsToDisplay)
	{
		cout << mapIterator->second << " with an edit distance of: " << mapIterator->first << "\n";
		mapIterator++; 
		iterationCounter++; 
	}

	return 0; 
}