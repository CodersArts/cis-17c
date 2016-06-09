/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.cpp
 * Author: michael
 * 
 * Created on June 8, 2016, 5:04 PM
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

#include "Graph.h"
using namespace std;

typedef vector<string>::iterator vecSIt;
typedef vector<Edge>::iterator vecEIt;
typedef set<string>::iterator setSIt;

Graph::Graph( ) {
	vertexSize = 0;
}

Graph::~Graph( ) {
}

void Graph::addVertex(string name){
	vertexs.push_back( name );
	vertexSize++;
}

void Graph::addEdge(string src, int weight, string dest){
	Edge edge( src, weight, dest );
	edges.push_back( edge );
}

void Graph::minSpan(){
	//get edges sorted by weight
	sort( edges.begin(), edges.end() );
	vector<Edge> shortest;
	set<string> *visited = new set<string>;
	
	for( vecEIt it = edges.begin(); it != edges.end(); ++it ){
//		cout << it->GetSource() << " to " << it->GetDestination() << endl;
		//if src vertex is visted
		if( formsCycle( visited, *it ) ) {
			cout << "ignoring " <<  it->GetSource() << " to " << it->GetDestination() << endl;
			continue;
		} else {
			cout << it->GetSource() << " to " << it->GetDestination() << endl;
			shortest.push_back( *it );
			visited->insert( it->GetSource() );
			visited->insert( it->GetDestination() );
		}
	}
	
	for( vecEIt it = shortest.begin(); it != shortest.end(); ++it ){
		cout<< it->GetSource() << ", " << it->GetWeight() << ", " << it->GetDestination() << endl;
	}
	
	delete visited;
}

bool Graph::formsCycle( set<string>* visited, Edge current ) {
	string src = current.GetSource();
	string dest = current.GetDestination();
	bool f[] = {false, false};
	for( setSIt it = visited->begin(); it != visited->end(); ++it ){
		cout << "\tform" << *it << endl;
		if( *it == src ){
			f[0] = true;
		}
		if( *it == dest ){
			f[1] = true;
		}
	}
	
	if( f[0] && f[1] ){
		return true;
	} else {
		return false;
	}
}

void Graph::shortestPath(){
	
}


