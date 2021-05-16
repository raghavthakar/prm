#include<iostream>
#include<list>
#include<random>
#include<chrono>
#include<cmath>

#define MAP_LENGTH 1000
#define CLUSTER_RADIUS 2000
#define CLUSTER_NUMBER 5

using namespace std;

class Node
{
  //Store info of the location occupied
  int col;
  int row;

  //This list stores pointer to all connected nodes
  list<Node*> connections;

public:
  //Constructor
  Node(int col, int row)
  {
    this->col=col;
    this->row=row;
  }

  //Returns the column number
  int getCol()
  {
    return col;
  }

  //Returns the row number
  int getRow()
  {
    return row;
  }

  //Add connection
  void addConnection(Node* connection)
  {
    connections.push_back(connection);
  }

  //Display info of the node
  void display()
  {
    cout<<"Column is: "<<col<<endl;
    cout<<"Row is: "<<row<<endl;
  }

  void displayMinimal()
  {
    cout<<col<<","<<row;
  }

  void displayConnections()
  {
    for(list<Node*>::iterator it=connections.begin();
        it!=connections.end(); it++)
    {
      (*it)->displayMinimal();
      cout<<"\t";
    }
  }
};

class Graph
{
  public:
  //Conatins all the node in the graph
  list<Node> all_nodes;

  //Returns the distance between two nodes
  double distanceBetween(Node n1, Node n2)
  {
    return sqrt(pow(n1.getCol()-n2.getCol(), 2)
            +pow(n1.getRow()-n2.getRow(), 2));
  }

  //Generates a random configuration in the workspace
  //and returns a node on it
  Node* generateRandomConfig()
  {
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    Node* x_rand = new Node(mt()%MAP_LENGTH, mt()%MAP_LENGTH);
    return x_rand;
  }

  //Tells whether the random configuration is legal to be
  //added to the graph or not
  bool isLegal(Node* x_rand)
  {
    return true;
  }

  //make edges in cluster
  void createCluster(Node* x_rand)
  {
    for(list<Node>::iterator i=all_nodes.begin();
        i!=all_nodes.end(); i++)
    {
      if(distanceBetween(*i, *x_rand)<CLUSTER_RADIUS)
      {
        i->addConnection(x_rand);
        x_rand->addConnection(&(*i));
      }
    }
  }

  void addNode(Node* x_rand)
  {
    //Push the random node into list of all nodes
    this->all_nodes.push_back(*x_rand);
  }
};

int main()
{
  Graph main_graph;

  Node* x_root;
  Node* x_rand;

  //main loop
  for(int i=0; i<7; i++)
  {
    //randomly smaple a point on the workspace
    x_rand = main_graph.generateRandomConfig();
    cout<<"The randomly sampled point is: \n";
    x_rand->display();

    //reiterate if the random node is illegal
    if(!main_graph.isLegal(x_rand))
    {
      i--;
      continue;
    }
    //if not illegal then simply add to graph and connect to neighbours
    else
    {
      main_graph.createCluster(x_rand);
      main_graph.addNode(x_rand);
    }
  }

  //show connections of all nodes
  for(list<Node>::iterator it=main_graph.all_nodes.begin();
      it!=main_graph.all_nodes.end(); it++)
  {
    (*it).displayConnections();
    cout<<endl;
  }

  return 0;
}
