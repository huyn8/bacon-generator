/*
* Author: Huy Nguyen
* Professor Michael Stiber
* Kevin Bacon Game
* Version 1
* 2/5/2021
* CSS 343
*
* BaconGenerator is used to process the input .txt from the Driver
* and generates a Kevin Bacon number accordingly
* This class will use the Graph2 class to calculate
* the Kevin Bacon number for each actor in the input file
*
* The required input will be a valid .txt file that
* contains properly formatted texts in order for the
* program to run accurately
*
*/
#include "BaconGenerator.h"

/*
* Default constructors and destructors
*/
BaconGenerator::BaconGenerator()
{
}

/*
* Default constructors and destructors
*/
BaconGenerator::~BaconGenerator()
{
}

/*
* This method will run the program and generates the output
*
* args:
* fileName - a text file in .txt format
*
* pre: a properly formatted txt file
*
* post: a list of actors/actresses and their Kevin Bacon numbers
*
* return: none
*/
void BaconGenerator::Execute(string fileName)
{
	//file object to read in input txt file
	ifstream fileObject;
	fileObject.open(fileName);
	
	if (fileObject.is_open())
	{
		//temp is used to store a line string read from the file
		//name is used to store the name of each of the actors/actresses in the file
		string temp, name;
		while (getline(fileObject, temp))
		{
			//if it is a new record and the line starts with the actor/actress name
			if (temp.find("\t") != 0)
			{
				name = temp.substr(0, temp.find("\t"));
				SortRecords(Split(name, temp), name);
			}
			//if the next line is a movie and not a new record 
			else
			{
				SortRecords(Split(name, temp), name);
			}
			count_actor_++;
		}
		fileObject.close();
	}
	PopulateGraph();
	graph_.CalculateBaconNumber();
	graph_.Display();
}

/*
* This method will splits the name of an actor/actresses and the movie name
*
* args:
* name - the name that will be used as a delimeter in splitting the name of an actor/actress and
* the movie name
*
* record - the rest of the record that will be used to split to extract the name of an actor/actress and
* the corresponding movie name
*
* pre: none
*
* post: none
*
* return: the name of an actor/actress
*/
string BaconGenerator::Split(string name, string record)
{
	//movie will store the return value of a movie
	string movie;

	if (record != "")
	{
		movie = record.substr(record.find_last_of('\t')+1);

		if (movie.find_first_of("(") != string::npos)
		{
			string completeMovie(movie.begin(), find(movie.begin(), movie.end(), ')') + 1);
			return completeMovie;
		}
		else if (movie.find_first_of("<") != string::npos)
		{
			movie = movie.substr(0, movie.find_last_of("<")-1);
		}
		else if (movie.find_first_of("{") != string::npos)
		{
			movie = movie.substr(0, movie.find_last_of("{")-1);
		}
		else if (movie.find_first_of("[") != string::npos)
		{
			movie = movie.substr(0, movie.find_last_of("[")-1);
		}
	}
	return movie;
}

/*
* This method will populate the internal map of the class for later processing purposes
* All unique movie names will be stored as a key and all actors and actresses will be
* stored as a value
* 
* Each key contains a unique movie, and each associated value is a vector of actors
* and actresses that appear in thh same movie that is the key
*
* args:
* name - the name of an actor/actress
*
* movie - the name of the movie
*
* pre: none
*
* post: the internal map will be populated with data (movies and actors/actresses)
* that will be later used to create a Graph object for calculating
* the Kevin Bacon number
*
* return: none
*/
void BaconGenerator::SortRecords(string movie, string name)
{
	if (movie == "" && name == "")
	{
		return;
	}
	//if the movie that an actor/actress is in, does not already exist in the map
	if (map_.find(movie) == map_.end())
	{
		//creating a new key-value pair in the map with key being the movie and 
		//value being a vector of actors/actresses
		vector<string> names;

		names.push_back(name);
		map_.insert(pair<string, vector<string>>(movie, names));
	}

	//if the movie already exists in the map
	else
	{
		//it also checks if a name of an actor/actress already exists in a movie 
		for (auto const& str : map_[movie])
		{
			if (str == name)
			{
				return;
			}
		}
		map_[movie].push_back(name);
	}
}

/*
* This method will initilized the Graph object by using the
* sorted map_ and Graph2 class internal methods
*
* args: none
*
* pre: map_ data are sorted and stored properly
*
* post: none
*
* return: none
*/
void BaconGenerator::PopulateGraph()
{
	graph_.Resize(count_actor_);
	for (auto const& pair : map_) 
	{
		for (int i = 0; i < pair.second.size(); i++)
		{
			if (pair.second.size() > 1)
			{
				for (int j = 1; j < pair.second.size(); j++)
				{
					graph_.InsertEdge(pair.second[i], pair.second[j]);
				}
			}
			else
			{
				graph_.InsertEdge(pair.second[i], "");
			}
		}
	}
}


