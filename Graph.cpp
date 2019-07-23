#include "Graph.hpp"
//made by Denislav Tsonev
//vertex class
Vertex::~Vertex()
{	
	Edge.clear();
}
std::string Vertex::getName()
{
	return name;
}

void Vertex::vertVisited()
{
	visit=true;
}

void Vertex::setVisit(bool foo)
{
	visit=foo;
}

void Vertex::setNumber(unsigned long num)
{
	tentWeight=num;
}
bool Vertex::isVisit()
{
	return visit;
}

unsigned long Vertex::getNumber()
{
	return tentWeight;
}

bool Vertex::Compare::operator()(Vertex *n1, Vertex *n2) const
{
	//compares the numbers of the nodes
	return lessThan ? n1->getNumber()< n2->getNumber() : n1->getNumber()>=n2->getNumber();
	
  
}


//graph class
Graph::~Graph()
{	//gets rid of the pointers in the graph map then clears it
	std::map<std::string,Vertex*>::iterator it;
	for(it=nodeVec.begin();it!=nodeVec.end();++it)
	{	
		if(it->second!=nullptr)
		{
			delete (it->second);
		}
	}
	nodeVec.clear();
}

void Graph::addVertex(std::string label)
{
	//creates a new object and pointer, then pushes it back
	Vertex* tempVert=new Vertex(label);
	nodeVec[label]=tempVert;
}

void Graph::removeVertex(std::string label)
{
	
	//just removes the vertex from the map 
	delete (nodeVec.find(label))->second;
	nodeVec.erase(label);
	
	
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{	
		//finds the vertex associated with the string given and then we access it's edge map,
		//we then create another entry in the map by using [] and creating an adjacent node edge and adding the distance
		((nodeVec.find(label1))->second)->Edge[(nodeVec.find(label2))->second]=weight;
		((nodeVec.find(label2))->second)->Edge[(nodeVec.find(label1))->second]=weight;
}
void Graph::removeEdge(std::string label1, std::string label2)
{	
		//finds the vertex at that string and then we access the map of that vertex 
		//	which we can then erase from the edge map of that vertex and wont be an adjacent node
		((nodeVec.find(label1))->second)->Edge.erase((nodeVec.find(label2))->second);
		((nodeVec.find(label2))->second)->Edge.erase((nodeVec.find(label1))->second);
	
	
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
{
	//resets all of the vertices back to INF and sets the visit to false
	std::map<std::string,Vertex*>::iterator it;
	for(it=nodeVec.begin();it!=nodeVec.end();++it)
	{
		(it->second)->setNumber(INF);
		(it->second)->setVisit(false);
	}
	
	std::map<Vertex*,unsigned long>::iterator adjIt;
	//get the starting vertex by finding it in the map 
	Vertex* startVertex=nodeVec.find(startLabel)->second;
	//set the weight of it to 0
	startVertex->setNumber(0);
	//mark it as visited
	startVertex->vertVisited();
	startVertex->prev=nullptr;
	//push it into the list
	
	minVertex.insert(startVertex);
	
	//while the list isn't empty
	while(!minVertex.empty())
	{	//get the front of the list
	
		Vertex* tempVert=minVertex.min();
		//then delete it 
		minVertex.removeMin();
		//get the node's edges and iterate through them
		for(adjIt=tempVert->Edge.begin();adjIt!=tempVert->Edge.end();++adjIt)
		{	//get the weight of the current node
			unsigned long currWeight=tempVert->getNumber();
			//get the weight of the next node in the map
			unsigned long nextWeight=(adjIt->first)->getNumber();
			//and if that node is not visited
			if(!((adjIt->first)->isVisit()))
			{	//and if the weight of the current node plus the distance is smaller than the next nodes weight
				if((currWeight+(adjIt->second))<nextWeight)
				{	//we set then set the vertex's weight to whatever the distance plus the previous node is
					(adjIt->first)->setNumber((currWeight+(adjIt->second)));
					(adjIt->first)->prev=tempVert;
					
				}
				//if also it isn't visited then we push it back to the list to iterate through it's other adjacent vertices
				
				minVertex.insert((adjIt->first));
			}
			
			
		}
		//mark that vertex as visited once you go through all of it's unvisited adjacent nodes
		tempVert->vertVisited();
		
	}
	
	//a traversal from the last node to the beginning 
	for(Vertex* trav=(nodeVec.find(endLabel))->second;trav!=nullptr;trav=trav->prev)
	{	//inserts it into the vector
		path.insert(path.begin(),trav->getName());
		
	}
	
	//returns the weight of the end node as it will be the number of the shortest path
	return ((nodeVec.find(endLabel)->second)->getNumber());
}



