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
#pragma once
#include <string>
#include <fstream>
#include <iostream> 
#include <iterator> 
#include <map> 
#include <vector>
#include "Graph2.h"

using namespace std;

class BaconGenerator
{
public:
	/*
	* Default constructors and destructors
	*/
	BaconGenerator();
	~BaconGenerator();

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
	void Execute(string fileName);

private:
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
	string Split(string name, string record);

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
	void SortRecords(string movie, string name);

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
	void PopulateGraph();

	/*
	* count_actor_ will be to count how many actors and actresses there are
	* in a given text file
	*/
	int count_actor_;

	/*
	* map_ will be used to store, sort the input data 
	* after that, the map_ will be used to initilized the Graph object
	*/
	map<string, vector<string>> map_;

	/*
	* graph_ object will be used to perform Kevin Bacon number 
	* calculation for an actor or actress
	* the calculation method can be found in Graph2.h pr Graph2.cpp
	*/
	Graph2 graph_;
};

