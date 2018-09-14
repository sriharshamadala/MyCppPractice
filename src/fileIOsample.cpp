#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

bool my_predicate(char c)
{
	if ( (c>=65 && c<=90) || (c>=97 && c<=122))
		return false;
	else
		return true;
}

int main()
{
	ifstream readfile;
	ofstream writefile;
	readfile.open("textToHash.txt");
	writefile.open("wordHash.txt");
	string line, word;
	if ( readfile.is_open())
	{
		while (getline(readfile,line))
		{
//			cout << line <<endl;
			istringstream linestream(line);
			while(linestream>>word)
			{
				word.erase(std::remove_if(word.begin(), word.end(), my_predicate), word.end());
				writefile << word << endl;
			}
		}
		readfile.close();
		writefile.close();
	}
	else
		cout << "failed to open\n";

	return 0;
}
