/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.h
 *
 * Created on June 8, 2016, 5:04 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

/*
 unable to finish my graph file in time the partial code of which can be viewed at
 https://github.com/angrymasteryoda/cis-17c/tree/myGraph/final/final
 */
#include <iostream>
#include <list>
#include <set>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    private:
        int nVert;//number of vertices
        int *parent;
        vector<string> name;
        list<pair<int,int> > *adj;
        void DFS(int,bool *);
        void unionVer(int,int);
        bool isCycle(int,int);
        int find(int);
    public:
        Graph(int);//constructor
        ~Graph();
        void addEdge(string,string,int);
        void addNames(vector<string>);
        void krusMST();//Kruskal’s Minimum Spanning Tree (MST)
        void shortestPath(string,string);//shortest path between two points with Dijkstra's algorithm
};

#endif /* GRAPH_H */

