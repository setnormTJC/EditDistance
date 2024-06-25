#include <iostream>
#include <string>
#include <vector>
#include<fstream> 
#include<iomanip>

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

/*Hamming distance assumes strings of same length - this method returns -1 other wise*/
int calcHammingDistance(const string& s1, const string& s2)
{
	int hammingDistance = 0; 

	if (s1.length() != s2.length())
	{
		cout << "Strings are not same length\n";
		return -1; 
	}

	for (int i = 0; i < s1.length(); i++)
	{
		if (s1.at(i) != s2.at(i))
		{
			hammingDistance++; 
		}
	}
	if (hammingDistance == s1.length())
	{
		cout << "The two strings have ZERO matching characters at same indices (maximal Hamming distance)\n";
	}
	return hammingDistance; 
}

static int recursiveCallCount = 0; 
int recursiveCalcLevenshteinDistance(const string& a, const string& b)
{

	recursiveCallCount++;
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

int main()
{
	string s1 = "Mikayla";
	string s2 = "Miniya";

	//cout << "Hamming distance between " << s1 << " and " << s2 << " is: "
	//	<< calcHammingDistance(s1, s2) << endl; 

	cout << "Levenshtein distance between " << s1 << " and " << s2 << " is :" 
		<< recursiveCalcLevenshteinDistance(s1, s2) << "\n";


	cout << "MAX POSSIBLE distance between the two strings is: " << std::max(s1.length(), s2.length()) << "\n";

	cout << "\nTotal number of recursive calls: " << recursiveCallCount << "\n";
	return 0; 
}