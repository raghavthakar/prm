#ifndef NODE_H
#define NODE_H
#include<list>

using namespace std;

class Node
{
  //Store info of the location occupied
  int col;
  int row;
  //Store the distance of the noee from start
  double distance;
  //This list stores pointer to all connected nodes
  list<Node*> connections;

public:
  //Constructor
  Node(int col, int row);
  //Returns the column number
  int getCol();
  //Returns the row number
  int getRow();
  //Return the distance
  double getDistance();
  //Write node data to a csv file
  void writeToCSV();
  //Add connection
  void addConnection(Node* connection);
  //Returns an iterator pointing to start of list
  list<Node*>::iterator getConnectionsBegin();
  //Returns an iterator pointing to end of list
  list<Node*>::iterator getConnectionsEnd();
  //Get number of connections
  int getNumberOfConnections();
  //Display info of the node
  void display();
  //Displays info in comapct manner
  void displayMinimal();
  //Displays all of the connection of a node
  void displayConnections();
};

#endif
