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

/*NOTE that this is the TRANSPOSE of the matrix on the Wikipedia page*/
int calcIterativeLevenshtein(string s, string t)
{
	vector<vector<int>> d;

	//init all matrix elements to 0:
	for (int i = 0; i < s.length() + 1; i++)
	{
		vector<int> row;
		for (int j = 0; j < t.length() + 1; j++)
		{
			row.push_back(0);
		}
		d.push_back(row);
	}


	for (int i = 0; i <= s.length(); i++)
	{
		d[i][0] = i;
	}

	for (int j = 0; j <= t.length(); j++)
	{
		d[0][j] = j;
	}


	int substitutionCost = 0;
	for (int j = 1; j <= t.length(); j++)
	{
		for (int i = 1; i <= s.length(); i++)
		{
			if (s[i - 1] == t[j - 1]) //differs from Wikipedia approach
			{
				substitutionCost = 0;
			}

			else
			{
				substitutionCost = 1;
			}

			int x = d[i - 1][j] + 1;
			int y = d[i][j - 1] + 1;
			int z = d[i - 1][j - 1] + substitutionCost;

			d[i][j] = std::min({ x, y, z });
		}
	}

	//printMatrix(d);

	return d[s.length()][t.length()];

}



/*acts as a sort of filter to prevent an expensive number of words from having their edit distances calculated
ALSO only returns words with SAME FIRST letter (uncommon to get wrong?)*/
vector<string> getWordsWithinNChars(int N, const string& startWord, const vector<string>& allWords)
{
	vector<string> wordsWithinNChars;

	for (auto& word : allWords)
	{

		int charCountDifference = startWord.length() - word.length();

		if ((startWord[0] == word[0]) && abs(charCountDifference) < N) //same start char!
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

		int currentWordLevDistance = calcIterativeLevenshtein(startWord, finishWords.at(i));

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
				<< " with an edit distance of " << wordsAndTheirLevenshteinDistance.begin()->first << "\n";
		}
	}

	return wordsAndTheirLevenshteinDistance;
}


int main()
{
	vector<string> allWords = getDictionaryWords();

	string startWord = "accomodate"; //absence

	int stringLengthDifferenceLimit = 4; //ex: misspelling "character" as "cat" will not get detected 
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

	int desiredNumberOfNeighborsToDisplay = 15;
	cout << startWord << " is most similar to the following " << desiredNumberOfNeighborsToDisplay << " words ...\n";

	auto mapIterator = resultingMap.begin();
	int iterationCounter = 0;
	while (iterationCounter < desiredNumberOfNeighborsToDisplay)
	{
		cout << mapIterator->second << " with an edit distance of: " << mapIterator->first << "\n";
		mapIterator++;
		iterationCounter++;
	}

	return 0;
}