#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <list>

#define MAP_LENGTH 1000
#define CLUSTER_RADIUS 75
#define CLUSTER_NUMBER 5

using namespace std;

class Graph
{
public:
  //Contains all the node in the graph
  list<Node> all_nodes;

  //Returns the distance between two nodes
  double distanceBetween(Node n1, Node n2);
  // Clears the CSV files
  void clearCSV();
  //Generates a random configuration in the workspace
  //and returns a node on it
  Node* generateRandomConfig();
  //Tells whether the random configuration is legal to be
  //added to the graph or not
  bool isLegal(Node* x_rand);
  //make edges in cluster
  void createCluster(Node* x_rand);
  //add the node to the graph
  void addNode(Node* x_rand);
};

#endif
