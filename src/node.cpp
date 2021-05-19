#include <iostream>
#include <fstream>
#include "node.h"

using namespace std;

//Constructor
Node::Node(int col, int row)
{
  this->col=col;
  this->row=row;
}

//Returns the column number
int Node::getCol()
{
  return col;
}

//Returns the row number
int Node::getRow()
{
  return row;
}

//Return the distance
double Node::getDistance()
{
  return (distance);
}

//Write node data to a csv file
void Node::writeToCSV()
{
  ofstream csv_file;
  csv_file.open("graph.csv", ios::app);

  csv_file<<getCol()<<","<<getRow()<<",";

  for(list<Node*>::iterator it=connections.begin();
      it!=connections.end(); it++)
  {
    csv_file<<(*it)->getCol()<<","<<(*it)->getRow()<<",";
  }
  csv_file<<endl;

  csv_file.close();
}

//Add an edge between this node and a connection node
void Node::addConnection(Node* connection)
{
  connections.push_back(connection);
}

//Returns an iterator pointing to start of list
list<Node*>::iterator Node::getConnectionsBegin()
{
  return connections.begin();
}

//Returns an iterator pointing to end of list
list<Node*>::iterator Node::getConnectionsEnd()
{
  return connections.end();
}

//Get number of connections
int Node::getNumberOfConnections()
{
  return connections.size();
}

//Display info of the node
void Node::display()
{
  cout<<"Column is: "<<getCol()<<endl;
  cout<<"Row is: "<<getRow()<<endl;
}

//Displays info in comapct manner
void Node::displayMinimal()
{
  cout<<col<<","<<row;
}

void Node::displayConnections()
{
  if(getNumberOfConnections())
  {
    for(list<Node*>::iterator it=connections.begin();
        it!=connections.end(); it++)
    {
      (*it)->displayMinimal();
      cout<<"\t";
    }
  }
  else
  {
    cout<<"Bruh";
  }
}
