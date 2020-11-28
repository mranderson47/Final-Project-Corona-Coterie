#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Create node structure for our date, each object contains the data associated with each event
struct Node
{
	
	string date;
	string province;
	string country;
	string confirmed;
	string deaths;
	string revovered;


};

int main()
{
	cout << "Welcome to the Corona Coterie Data Index!" << endl;


	//Load our file stream.
	fstream fin;
	string file = "data.csv";

	//Open the data to be parsed.
	fin.open(file);

	//***********PARSING************//

	//Determine if we successfully opened the file.
	if (fin.is_open())
	{
		int index;
		string line;
		getline(fin, line);
		Node node;
		
		//For each line, make a new node
		while (!fin.eof())
		{
			getline(fin, line);
			//Start our index
			index = line.find(",");

			//Store the date for each node
			node.date = line.substr(index + 1, line.find(",", index + 1) - index - 1);
			
			//Update the index
			index = line.find(",", index + 1);

			//Store the province for each node
			node.province = line.substr(index + 1, line.find(",", index + 1) - index - 1);

			//Update the index
			index = line.find(",", index + 1);

			//Store the country for each node
			node.country = line.substr(index + 1, line.find(",", index + 1) - index - 1);

			//Update the index
			index = line.find(",", index + 1);

			//Store the confirmed number of cases
			node.confirmed = line.substr(index + 1, line.find(",", index + 1) - index - 1);

			//Update the index
			index = line.find(",", index + 1);

			//Store the  number of deaths
			node.deaths = line.substr(index + 1, line.find(",", index + 1) - index - 1);

			//Update the index
			index = line.find(",", index + 1);

			//Store the  number of recovered
			node.revovered = line.substr(index + 1, line.find(",", index + 1) - index - 1);

			//Update the index
			index = line.find(",", index + 1);


			
			//*****Test printing data to make sure it is accurate*********//
			
			cout << node.date << " " << node.province << " " << node.country << " " << node.confirmed << " " << node.deaths << " " << node.revovered << endl;



		}
		
		cout << "Finished loading all data!" << endl;

	}
	//If we were not able to open the file, exit the program.
	else
	{
		cout << "File cannot be opened! Please Try Again." << endl;
		return 0;
	}


};