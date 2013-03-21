#include "Graph.hpp"
#include <cassert>
#include <algorithm>

using namespace std;

void Vertex::updateGrid() {
	grid = sf::Vector2i(int(pos.x/SCRWIDTH*GRIDX), int(pos.y/SCRHEIGHT*GRIDX));
}

Graph::Graph() {}
Graph::Graph(int n) : vertices(n) {}

void Graph::clear()
{
	vertices = vector<Vertex> (0);
}

//Checks if vertices a and b are adjacent

bool Graph::areConnected(int a, int b) const
{
	assert(a >= 0); assert(a < getVertexCount());
	assert(b >= 0); assert(b < getVertexCount());
	assert(a != b);
	return find(vertices[a].adj.begin(), vertices[a].adj.end(), b) != vertices[a].adj.end();
}

//Returns a vector containing all the adjacent vertices of vertex n
const std::vector<int>& Graph::getConnections(int n) const
{
	assert(n >= 0); assert(n < getVertexCount());
	return vertices[n].adj;
}

//Returns degree of vertex n
int Graph::getDegree(int n) const
{
	assert(n >= 0); assert(n < getVertexCount());
	return vertices[n].adj.size();
}

//Connects vertices a and b
void Graph::connect(int a, int b)
{
	assert(a >= 0); assert(a < getVertexCount());
	assert(b >= 0); assert(b < getVertexCount());
	assert(a != b);
	assert(!areConnected(a, b));
	vertices[a].adj.push_back(b);
	vertices[b].adj.push_back(a);
}

//Disconnects vertices a and b
void Graph::disconnect(int a, int b)
{
	assert(a >= 0); assert(a < getVertexCount());
	assert(b >= 0); assert(b < getVertexCount());
	assert(a != b);
	assert(areConnected(a, b));
	vertices[a].adj.erase(find(vertices[a].adj.begin(), vertices[a].adj.end(), b));
	vertices[b].adj.erase(find(vertices[b].adj.begin(), vertices[b].adj.end(), a));
}



//Returns a vector containing all the friend vertices of vertex n




//Returns the number of vertices
int Graph::getVertexCount() const
{
	return vertices.size();
}

//Adds a new vertex to the graph and returns its id
int Graph::addVertex()
{
	vertices.push_back(Vertex());
	return vertices.size()-1;
}


Vertex& Graph::operator[](int i)
{
	assert(i >= 0); assert(i < getVertexCount());
	return vertices[i];
}

const Vertex& Graph::operator[](int i) const
{
	assert(i >= 0); assert(i < getVertexCount());
	return vertices[i];
}

//Reads a graph from .gra format
istream& operator>> (istream& in, Graph &g)
{
	int order;
	in >> order;
	g.clear();
	for(int i = 0; i < order; i++)
		g.addVertex();

	int size;
	in >> size; //arestes
	int foo = 2*size+1; //al no ser dirigit, l'aresta a(u,v), es conta per a u i v.

	int trash;
	//grau input
	for (int i = 0; i < order; ++i) {
		in >> trash;
	}

	//llegir adj i pos
	vector<int> adj(foo);

	for (int i = 0; i < foo; ++i) {
		in >> adj[i];
	}

	vector<int> pos(order+1) ;
	for (int i = 0; i < order+1; ++i) {
		in >> pos[i];
	}
	//end llegir adj i pos

	for (int i = 0; i < order; ++i) {
		for (int j = pos[i]; j < pos[i+1]; ++j) {
			if(i < adj[j])
				g.connect(i, adj[j]);
		}
	}

	return in;
}

//Writes the graph in a human-readable format. For debugging
ostream& operator<< (ostream& out, Graph &g)
{
	out << "*** Graph ***" << endl;
	for(int i = 0; i < g.getVertexCount(); i++)
	{
		out<<"Vertex "<<i<<": "<<endl;

		out<<"    Edges: ";
		const vector<int>& edges = g.getConnections(i);
		for(int j = 0; j < (int)edges.size(); j++)
			out<<edges[j]<<" ";
		if(edges.size() == 0) out << "(none)";
		out<<endl;

	}

	return out;
}
