#include <iostream>
#include <fstream>
#include <list>
#include <random>
#include <chrono>
#include <cmath>
#include <unistd.h>

#define MAP_LENGTH 1000
#define CLUSTER_RADIUS 75
#define CLUSTER_NUMBER 5

using namespace std;

class Node
{
  //Store info of the location occupied
  int col;
  int row;

  //Store the distance of the noee from start
  int distance;

  //This list stores pointer to all connected nodes
  list<Node*> connections;

  public:
  //Constructor
  Node(int col, int row)
  {
    this->col=col;
    this->row=row;
    this->distance=10000;
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

  //Return the distance
  // double getDistance()
  // {
  //   return (distance);
  // }

  void writeToCSV()
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

  //Add connection
  void addConnection(Node* connection)
  {
    connections.push_back(connection);
  }

  //Returns an iterator pointing to start of list
  list<Node*>::iterator getConnectionsBegin()
  {
    return connections.begin();
  }

  //Returns an iterator pointing to end of list
  list<Node*>::iterator getConnectionsEnd()
  {
    return connections.end();
  }

  //Get number of connections
  int getNumberOfConnections()
  {
    return connections.size();
  }

  //Display info of the node
  void display()
  {
    cout<<"Column is: "<<getCol()<<endl;
    cout<<"Row is: "<<getRow()<<endl;
  }

  //Displays info in comapct manner
  void displayMinimal()
  {
    cout<<col<<","<<row;
  }

  //Displays all of the connection of a node
  void displayConnections()
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

  // Clears the CSV files
  void clearCSV()
  {
    ofstream csv_file;
    csv_file.open("graph.csv");
    csv_file.close();
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
  void addNode(Node* x_rand)
  {
    //Push the random node into list of all nodes
    this->all_nodes.push_back(*x_rand);
  }
};

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
  main_graph.createCluster(x_start);
  main_graph.addNode(x_start);

  //Add goal node to graph
  main_graph.createCluster(x_goal);
  main_graph.addNode(x_goal);

  //Clear the csv where graph willbe written
  main_graph.clearCSV();

  //main loop
  for(int i=0; i<500; i++)
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
