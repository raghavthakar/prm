#include <iostream>
#include <list>
#include <unistd.h>
#include "graph.h"
#include "node.h"

#define NUM_NODES 3

using namespace std;

Graph dijkstra(Graph main_graph)
{
  //start from start, set the distance of all connections
  //pick the connection with lowest distance, and push it to another list
  //set distance of all connections if lower than already present distance
  //pick cinnection wid lwoest dist, push it to another list
}

int main()
{
  Graph main_graph;

  Node* x_rand;

  int start_col, start_row, goal_col, goal_row;

  //Info on starting point
  cout<<"Enter starting column: ";
  cin>>start_col;
  cout<<"Enter starting row: ";
  cin>>start_row;
  Node* x_start=new Node(start_col, start_row);

  //Info on goal point
  cout<<"Enter goal column: ";
  cin>>goal_col;
  cout<<"Enter goal row: ";
  cin>>goal_row;
  Node* x_goal=new Node(goal_col, goal_row);

  //Add starting node to graph
  main_graph.addNode(x_start);

  //Add goal node to graph
  main_graph.createCluster(x_goal);
  main_graph.addNode(x_goal);

  //Clear the csv where graph willbe written
  main_graph.clearCSV();

  //main loop
  for(int i=0; i<NUM_NODES; i++)
  {
    //randomly smaple a point on the workspace
    x_rand = main_graph.generateRandomConfig();
    // cout<<"The randomly sampled point is: \n";
    // x_rand->display();

    //reiterate if the random node is illegal
    if(!main_graph.isLegal(x_rand))
    {
      i--;
      continue;
    }
    //if not illegal then simply add to graph and connect to neighbours
    else
    {
      //add edges with neighbours
      main_graph.createCluster(x_rand);
      //add to list of all nodes
      main_graph.addNode(x_rand);
    }
  }

  //Loop to write node data into csv file
  for(list<Node>::iterator it=main_graph.all_nodes.begin();
      it!=main_graph.all_nodes.end(); it++)
  {
    (*it).writeToCSV();
  }

  // main_graph=dijkstra(main_graph);

  return 0;
}
