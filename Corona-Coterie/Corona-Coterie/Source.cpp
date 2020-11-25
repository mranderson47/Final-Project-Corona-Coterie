#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
	string province;
	string country;
	int confirmed;
	int deaths;
	int revovered;

};

int main()
{
	//Load our file stream.
	fstream fin;
	string file = "data.csv";

	//Open the data to be parsed.
	fin.open(file);

	//Determine if we successfully opened the file.
	if (fin.is_open())
	{

	}
	//If we were not able to open the file, exit the program.
	else
	{
		cout << "File cannot be opened! Please Try Again." << endl;
		return 0;
	}


};