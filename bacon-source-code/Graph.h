/*
* Author: Huy Nguyen
* Professor Michael Stiber
* Kevin Bacon Game
* Version 1
* 2/5/2021
* CSS 343
*
* Graph2 is used to create a network relationships between actors
* and actresses for the calculation of a Kevin Bacon number accordingly
* 
* Adjacency list approach will be used to represent a Graph2 object
* 
* First, a network relationship will be created properly, then
* using the Breadth First Search method or BFS to find the minimal
* distance between Kevin Bacon and another actor or actress
*
*/
#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;
class Graph2
{
public:
	/*
	* Default constructors and destructors
	*/
	Graph2();
	~Graph2();

	/*
	* This method will help construct the graph by creating an edge to
	* connect the two vertices together
	*
	* args:
	* source - the source vertex on one end of the edge
	* destination - the vertex on the other end that connects to source
	*
	* pre: none
	*
	* post: a network of graph is constructed 
	*
	* return: none
	*/
	void InsertEdge(string source, string destination);

	/*
	* This method will find if a vertex already exists in the graph network
	*
	* args:
	* target - is the name of the vertex that needs to be searched
	*
	* pre: a non-empty graph
	*
	* post: none
	*
	* return: true if a vertex exists/found, false otherwise
	*/
	bool Find(string target);

	/*
	* This method will find if a neighbor vertex already exists in the graph network
	*
	* args:
	* v - is the list of edges or neighbors of the source vertex 
	* target - is the name of the neighbor vertex that needs to be searched
	*
	* pre: a non-empty graph
	*
	* post: none
	*
	* return: true if a neighbor vertex exists/found, false otherwise
	*/
	bool FindNeighbor(vector <string> v, string target);

	/*
	* This method will resize the initilize the size for
	* the adjacency list adj_list_
	*
	* args:
	* size - size of the adj_list_
	*
	* pre: none
	*
	* post: none
	*
	* return: none
	*/
	void Resize(int size);

	/*
	* This method will return the index of the correct postion for
	* whenever a new vertex/neighbor is inserted
	*
	* args:
	* target - the name of the vertex
	*
	* pre: a none empty graph
	*
	* post: none
	*
	* return: the index of the target if found
	* -1 otherwise
	*/
	int RetrieveIndex(string target);

	/*
	* This method will return a source index from all 
	* of the vertices and used by the CalculateBaconNumber method
	*
	* args:
	* target - the name of the vertex
	*
	* pre: a none empty graph
	*
	* post: none
	*
	* return: the index of the target if found
	* -1 otherwise
	*/
	int IndexOf(string target);

	/*
	* This method will calculate Kevin Bacon number for all of
	* the actors and actresses in the graph
	* 
	* It uses BFS approach to find the minimal distance between
	* two vertices The source vertex will always be Kevin Bacon 
	* and the destination vertex will be any other related or unrelated
	* actor/actress. If an actor or actress does not have any relationship
	* with Kevin Bacon, infinity will be their associated number. Otherwise
	* any well-known actors or actresses will have the Bacon number from
	* 1 - 6
	*
	* args: none
	*
	* pre: a properly constructed graph
	*
	* post: a list of actors/actresses and their Kevin Bacon numbers
	*
	* return: none
	*/
	void CalculateBaconNumber();

	/*
	* This method displays the output as actor/actress name tab Kevin Bacon number
	*
	* args: none
	*
	* pre:  a properly constructed graph and all Kevin Bacon numbers are calculated 
	*
	* post: none
	*
	* return: none
	*/
	void Display();

private:
	//adj_list_ is the adjacency list representation of the a Graph object
	vector <vector<string>> adj_list_;

	//bacon_number_ is used to store the bacon number for each actor
	//this variable is used by the method CalculateBaconNumber
	vector<int> bacon_number_;

	//size_ is the size of the adj_list_
	int size_;
};