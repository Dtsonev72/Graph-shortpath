//Graph.hpp
#ifndef GRAPH_H
#define GRAPH_H
//made by Denislav Tsonev
#include "GraphBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <climits>
#include <iterator>

#define INF ULONG_MAX

class Vertex
{
	public:
	//constructors
	Vertex(std::string s,unsigned long num):name(s),tentWeight(num),visit(false) {};
	
	Vertex(std::string s):Vertex(s,INF){};
	
	~Vertex();//destructor
	void vertVisited();//marks the vert as visited
	void setVisit(bool foo);//sets the value of visited
	//sets the weight
	void setNumber(unsigned long num);
	//gets the name
	std::string getName();
	//checks to see if it is visited
	bool isVisit();
	unsigned long getNumber();
	std::map<Vertex*,unsigned long> Edge;
	Vertex* prev;
	//comparator class in order to keep the vertices in order 
	class Compare
	{
	  public:
		Compare(bool lessThan = true) : lessThan(lessThan) {};
		bool operator()(Vertex *n1,Vertex *n2) const;

	  private:
		bool lessThan;
	};
	
	//initialize members of the vertex
	private:
	std::string name;
	bool visit;
	unsigned long tentWeight;
	

};
	


class Graph:GraphBase
{
 public:
	void addVertex(std::string label);
	void removeVertex(std::string label);
	void addEdge(std::string label1, std::string label2, unsigned long weight);
	void removeEdge(std::string label1, std::string label2);
	unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
	//destructor
	~Graph();
	
 private:
 	
	//maps all of the vertices to a string
	std::map<std::string,Vertex*> nodeVec;
	//puts the nodes in a list to know which ones to traverse	
	HeapQueue<Vertex*, Vertex::Compare> minVertex;
	
};




#endif