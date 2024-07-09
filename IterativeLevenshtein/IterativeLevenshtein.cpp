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


void printMatrix(vector<vector<int>> matrix)
{
	for (auto& row : matrix)
	{
		for (auto& element : row)
		{
			cout << element << " "; 
		}
		cout << "\n";
	}
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

	printMatrix(d);

	return d[s.length()][ t.length()];

}


int main()
{
	string s = "Miniya";
	string t = "Mikayla"; 

	cout << "Lev. dist. between " << s << " and " << t << " is: "
		<< calcIterativeLevenshtein(s, t) << "\n";

	return 0; 
}