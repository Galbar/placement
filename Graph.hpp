#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <iostream>
#include "tools.hpp"

class Graph;

//Represents a vertex in the Graph
class Vertex {
		friend class Graph;
	private:
		std::vector<int> adj;

		//Disallows assigning vertices, like g[0] = g[1]
		//void operator=(const Vertex& b);
	public:
		sf::Vector2f pos;
		sf::Vector2f disp;
		sf::Vector2i grid;
		void updateGrid();
};
//Represents a non-directed graph
//Duplicate edges and edges from a vertex to itself are not allowed.
class Graph {
	private:
		//Vertex list
		std::vector<Vertex> vertices;

	public:
		//Creates an empty graph
		Graph();
		//Creates a graph with n disconnected vertices
		Graph(int n);
		//Clears the graph
		void clear();

		//Checks if vertices a and b are adjacent
		bool areConnected(int a, int b) const;
		//Returns a vector containing all the adjacent vertices of vertex n
		const std::vector<int>& getConnections(int n) const;
		//Returns degree of vertex n
		int getDegree(int n) const;
		//Connects vertices a and b
		void connect(int a, int b);
		//Disconnects vertices a and b
		void disconnect(int a, int b);


		//Returns the number of vertices
		int getVertexCount() const;

		//Adds a new vertex to the graph and returns its id
		int addVertex();

		Vertex& operator[](int i);
		const Vertex& operator[](int i) const;
};


//Reads a graph from .gra format
std::istream& operator>> (std::istream& in, Graph &g);
//Writes the graph in a human-readable format. For debugging
std::ostream& operator<< (std::ostream& out, Graph &g);

#endif
