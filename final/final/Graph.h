/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.h
 * Author: michael
 *
 * Created on June 8, 2016, 5:04 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>
#include "Edge.h"

using namespace std;

class Graph {
private:
	int vertexSize;
	vector<string> vertexs;
	vector<Edge> edges;
	bool formsCycle( set<string> *visited, Edge current );
public:
	Graph();
	virtual ~Graph();
	void addVertex( string name );
	void addEdge( string src, int weight, string dest );
	void minSpan();
	void shortestPath();

};

#endif /* GRAPH_H */

