#include <cmath>
#include <fstream>
#include <random>
#include <chrono>
#include "graph.h"

using namespace std;

//Returns the distance between two nodes
double Graph::distanceBetween(Node n1, Node n2)
{
  return sqrt(pow(n1.getCol()-n2.getCol(), 2)
          +pow(n1.getRow()-n2.getRow(), 2));
}

// Clears the CSV files
void Graph::clearCSV()
{
  ofstream csv_file;
  csv_file.open("graph.csv");
  csv_file.close();
}

//Generates a random configuration in the workspace
//and returns a node on it
Node* Graph::generateRandomConfig()
{
  mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
  Node* x_rand = new Node(mt()%MAP_LENGTH, mt()%MAP_LENGTH);
  return x_rand;
}

//Tells whether the random configuration is legal to be
//added to the graph or not
bool Graph::isLegal(Node* x_rand)
{
  return true;
}

//make edges in cluster
void Graph::createCluster(Node* x_rand)
{
  //make edge bw x_rand and all neighbouring nodes
  for(list<Node>::iterator i=all_nodes.begin();
      i!=all_nodes.end(); i++)
  {
    if(distanceBetween(*i, *x_rand)<CLUSTER_RADIUS)
    {
      i->addConnection(x_rand);
      x_rand->addConnection(&(*i));
    }
  }

  //if there are nodes with no edges then force make on with nearest node
  list<Node>::iterator nearest=all_nodes.begin();
  //find nearest node
  if(!x_rand->getNumberOfConnections())
  {
    for(list<Node>::iterator i=all_nodes.begin();
        i!=all_nodes.end(); i++)
    {
      if(distanceBetween(*i, *x_rand)<distanceBetween(*nearest, *x_rand))
        nearest=i;
    }
    //make edge with nearest node
    nearest->addConnection(x_rand);
    x_rand->addConnection(&(*nearest));
  }
}

//add the node to the graph
void Graph::addNode(Node* x_rand)
{
  //Push the random node into list of all nodes
  this->all_nodes.push_back(*x_rand);
}
