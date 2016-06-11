/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.cpp
 * 
 * Created on June 8, 2016, 5:04 PM
 */

/*
 unable to finish my graph file in time the partial code of which can be viewed at
 https://github.com/angrymasteryoda/cis-17c/tree/myGraph/final/final
 */

#include "Graph.h"

Graph::Graph(int n){
  nVert=n;
  adj=new list<pair<int,int> >[n];
  parent=new int[nVert];
  for(int i=0;i<nVert;i++)
    parent[i]=-1;
}

Graph::~Graph(){
  delete []adj;
  delete []parent;
}

void Graph::addNames(vector<string> names){
  name=names;
}

void Graph::addEdge(string a, string b,int d){
  //a --- First node
  //b --- Second node
  //d --- Distance between them
  //change the names of airports into numbers
  int x=0;
  int y=0;
  if(a.compare("SFO")==0)
    x=0;
  else if(a.compare("ORD")==0)
    x=1;
  else if(a.compare("JFK")==0)
    x=2;
  else if(a.compare("DFW")==0)
    x=3;
  else if(a.compare("MIA")==0) 
    x=4;
  else if(a.compare("LAX")==0) 
    x=5;
  else if(a.compare("BOS")==0) 
    x=6;
  

  if(b.compare("SFO")==0) 
    y=0;
  else if(b.compare("ORD")==0) 
    y=1;
  else if(b.compare("JFK")==0) 
    y=2;
  else if(b.compare("DFW")==0)
    y=3;
  else if(b.compare("MIA")==0)
    y=4;
  else if(b.compare("LAX")==0)
    y=5;
  else if(b.compare("BOS")==0)
    y=6;
  adj[x].push_back(make_pair(y,d));
  adj[y].push_back(make_pair(x,d));
}

//Kruskal’s Minimum Spanning Tree (MST)
void Graph::krusMST() {
  vector<pair< int, pair<int,int> > > ls;
  //sort all the edge
  //input the beginning vertex,end vertex, distance from the private list<int,int> adj
  list<pair<int,int> >::iterator it;
  for(int i=0;i<nVert;i++) {
    for(it=adj[i].begin();it!=adj[i].end();++it) {
      ls.push_back(make_pair((*it).second,make_pair(i,(*it).first)));
    }
  }
  sort(ls.begin(),ls.end());
  vector<pair< int, pair<int,int> > >::iterator it2=ls.begin();

  int weight=0;//weight of the tree
  set<int> s;
//Get the minimum spanning tree
  cout<<"The minimum spanning tree: "<<endl;
  for(;it2!=ls.end();++it2) {
    //Determine create circle or not
    if(!isCycle((*it2).second.first,(*it2).second.second)) {
      weight+=(*it2).first;
      s.insert((*it2).second.first);
      s.insert((*it2).second.second);
      cout<<name[(*it2).second.first]<<" --- "<<name[(*it2).second.second];
      cout<<"   "<<(*it2).first<<endl;
    }
  }
  cout<<"Weight: "<<weight<<endl;
}

//find the parent
int Graph::find(int x) {
  if(parent[x]==-1)
    return x;
  return find(parent[x]);
}

//Determine it creates circle after connect x and y node
bool Graph::isCycle(int x,int y) {
  // Iterate through all edges of graph, find subset of both
  // vertices of every edge, if both subsets are same, then 
  // there is cycle in graph.
  int xpar=find(x);
  int ypar=find(y);
  if(xpar==ypar) return true;
  unionVer(x,y);
  return false;
}

//put x and y into union
void Graph::unionVer(int x, int y) {
  int xset=find(x);
  int yset=find(y);
  parent[xset]=yset;
}

//shortest path between two points with Dijkstra's algorithm
void Graph::shortestPath(string a, string b){
  cout<<endl<<"Shortest path from BOS to LAX: "<<endl;
  int x=0;
  int y=0;
  if(a.compare("SFO")==0)
    x=0;
  else if(a.compare("ORD")==0)
    x=1;
  else if(a.compare("JFK")==0)
    x=2;
  else if(a.compare("DFW")==0)
    x=3;
  else if(a.compare("MIA")==0)
    x=4;
  else if(a.compare("LAX")==0)
    x=5;
  else if(a.compare("BOS")==0)
    x=6;

  if(b.compare("SFO")==0)
    y=0;
  else if(b.compare("ORD")==0)
    y=1;
  else if(b.compare("JFK")==0)
    y=2;
  else if(b.compare("DFW")==0)
    y=3;
  else if(b.compare("MIA")==0)
    y=4;
  else if(b.compare("LAX")==0)
    y=5;
  else if(b.compare("BOS")==0)
    y=6;

  struct Node{
    int order; //order
    int tempDis;
//    int name;
    int permDis;
    vector<pair<int,int> > neigbor;
    //pair(Distance of Edge, End Node)
  };
  list<pair<int,int> >::iterator it;
  Node *nodes=new Node[nVert];
  int currNode=x;
  for(int i=0;i<nVert;i++) {
    nodes[i].tempDis=0;
    nodes[i].permDis=0;
    nodes[i].order=0;
    it=adj[i].begin();
    for(;it!=adj[i].end();++it) {
      nodes[i].neigbor.push_back(make_pair((*it).second,(*it).first));
    }
    sort(nodes[i].neigbor.begin(),nodes[i].neigbor.end());
  }
//    _____________________
//    | Order# | Permanent |
//    | Number | Distance  |
//    ----------------------
//    |   Temp Distance    |
//    ----------------------
    int orderNum=0;
    nodes[currNode].order=(++orderNum);
    nodes[currNode].permDis=0;
    
    int *index=new int[nVert];
    for(int i=0;i<nVert;i++) {
      index[i]=i;
    }
     
    do {
      for(int i=0;i<nodes[currNode].neigbor.size();i++) {
        //set the temp distance to the node that doesn't have order number
        if(nodes[nodes[currNode].neigbor[i].second].order==0) {
          int dis=nodes[currNode].neigbor[i].first+nodes[currNode].tempDis;
          if(nodes[nodes[currNode].neigbor[i].second].tempDis==0||
              dis<nodes[nodes[currNode].neigbor[i].second].tempDis)
            nodes[nodes[currNode].neigbor[i].second].tempDis=dis;
        }
      }
      //sort the temp distance and get the node with lowest distance
      for(int k=0;k<nVert-1;k++) {
        for(int h=k+1;h<nVert;h++) {
          if(nodes[index[k]].tempDis>nodes[index[h]].tempDis) {
            int temp=index[k];
            index[k]=index[h];
            index[h]=temp;
          }
        }
      }
         
      //Finish the sort and get the node with lowest distance
      for(int k=0;k<nVert;k++) {
        if(nodes[index[k]].permDis==0&&nodes[index[k]].tempDis!=0) {
          currNode=index[k];
          break;
        }
      }
      nodes[currNode].order=(++orderNum);
      nodes[currNode].permDis=nodes[currNode].tempDis;
    } while(nodes[y].permDis==0);
 
    int length=nodes[y].permDis;
    list<pair<pair<int,int>,int> > path;
    list<pair<pair<int,int>,int> >::iterator it2;
    do {
      for(int i=0;i<nodes[currNode].neigbor.size();i++) {
        if((length-nodes[currNode].neigbor[i].first)==nodes[nodes[currNode].neigbor[i].second].permDis) {
          path.push_front(make_pair(make_pair(nodes[currNode].neigbor[i].second,currNode),nodes[currNode].neigbor[i].first));
          length=nodes[nodes[currNode].neigbor[i].second].permDis;
          currNode=nodes[currNode].neigbor[i].second;
          break;
        }
      }
    } while(length>0);
    
    //Output the path and the length
    for(it2=path.begin();it2!=path.end();++it2) {
      cout<<name[(*it2).first.first]<<" ----> "<<name[(*it2).first.second]<<"   "<<(*it2).second<<endl;
    }
    cout<<"The shortest length: "<<nodes[y].permDis<<endl;
    delete []nodes;
}