/*
* Author: Huy Nguyen
* Kevin Bacon Game
* Version 1
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
#include "Graph2.h"

/*
* Default constructors and destructors
*/
Graph2::Graph2()
{
}

Graph2::~Graph2()
{
}

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
void Graph2::Resize(int size)
{
	this->size_ = size;
	adj_list_.resize(size);
	bacon_number_.resize(size);
}

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
void Graph2::InsertEdge(string source, string destination)
{
	//when an actor/actress does not have any connections
	if (destination == "")
	{
		if (Find(source))
		{
			return;
		}
		else
		{
			int indexTemp = RetrieveIndex(source);
			adj_list_[indexTemp].push_back(source);
			return;
		}
	}

	//when an edge already exists
	int sourceIndex = RetrieveIndex(source);//the position of where the vertex will be inserted
	if (!Find(source))
	{
		adj_list_[sourceIndex].push_back(source);
		adj_list_[sourceIndex].push_back(destination);
	}

	//when the source vertex exists and the destination vertex does not
	else if(!FindNeighbor(adj_list_[sourceIndex], destination))
	{
		adj_list_[sourceIndex].push_back(destination);
	}
	
	int desIndex = RetrieveIndex(destination);//the position of where the vertex will be inserted

	//connecting the other end (from destination to source vertex)
	if (!Find(destination))
	{
		adj_list_[desIndex].push_back(destination);
		adj_list_[desIndex].push_back(source);
	}

	//when the destination vertex exists and the sorce vertex does not
	else if(!FindNeighbor(adj_list_[desIndex], source))
	{
		adj_list_[desIndex].push_back(source);
	}
	return;
}

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
bool Graph2::Find(string target)
{
	for (int i = 0; i < size_; i++)
	{
		if (adj_list_[i].size() == 0)
		{
			break;
		}
		if (adj_list_[i][0] == target)
		{
			return true;
		}
	}
	return false;
}

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
bool Graph2::FindNeighbor(vector<string> v, string target)
{
	for (auto const& i : v)
	{
		if (i == target)
		{
			return true;
		}
	}
	return false;
}

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
int Graph2::RetrieveIndex(string target)
{
	for (int i = 0; i < size_; i++)
	{
		if (adj_list_[i].size() == 0)
		{
			return i;
		}
		if (adj_list_[i][0] == target)
		{
			return i;
		}
	}
	return -1;
}

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
void Graph2::CalculateBaconNumber()
{
	//the queue is used to store verticies that will be visted in the BFS order
	list<int> queue;

	//the vector is used to mark if a vertex has already been visited 
	vector<bool> visited(size_);

	for (int i = 0; i < size_; i++) {
		visited[i] = false;
		bacon_number_[i] = -1;
	}

	//the index of Bacon Kevin in the graph
	int temp = RetrieveIndex("Bacon, Kevin (I)");
	visited[temp] = true;
	bacon_number_[temp] = 0;
	queue.push_back(temp);

	while (!queue.empty()) 
	{
		int u = queue.front();
		queue.pop_front();

		for (int i = 0; i < adj_list_[u].size(); i++)
		{
			int temp = IndexOf(adj_list_[u][i]);
			if (visited[temp] == false) 
			{
				visited[temp] = true;
				bacon_number_[temp] = bacon_number_[u] + 1;
				queue.push_back(temp);
			}
		}
	}
}

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
int Graph2::IndexOf(string target)
{
	for (int i = 0; i < size_; i++)
	{
		if (adj_list_[i].size() != 0)
		{
			if (target == adj_list_[i][0])
			{
				return i;
			}
		}	
	}
	return -1;
}


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
void Graph2::Display()
{
	for (int i = 0; i < size_; i++)
	{
		if (adj_list_[i].size() != 0)
		{
			if (bacon_number_[i] == -1)
			{
				cout << adj_list_[i][0] << "\t infinity" << endl;
			}
			else
			{
				cout << adj_list_[i][0] << "\t" << bacon_number_[i] << endl;
			}
		}
	}
}




