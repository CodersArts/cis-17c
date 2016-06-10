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
#include <math.h>
#include <climits>

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
	//have to make a disjunct set 
	// https://en.wikipedia.org/wiki/Disjoint-set_data_structure
	vector<Edge> shortest;
	
	for( vecSIt it = vertexs.begin(); it != vertexs.end(); ++it ){
		makeSet( *it );
	}
	
	sort( edges.begin(), edges.end() );
	for( vecEIt it = edges.begin(); it != edges.end(); ++it ){
		string r1 = find( it->GetSource() );
		string r2 = find( it->GetDestination() );
		if( r1 != r2 ){
			shortest.push_back( *it );
			unionize( r1, r2 );
		}
		
	}
	
	for( vecEIt it = shortest.begin(); it != shortest.end(); ++it ){
		cout<< it->GetSource() << ", " << it->GetWeight() << ", " << it->GetDestination() << endl;
	}
}

string Graph::find( string vertex ){
	if (parent[vertex] == vertex) {
		return parent[vertex];
	} else{ 
		return find(parent[vertex]);	
	}
}

void Graph::unionize( string v1, string v2 ){
	if( rank[v1] > rank[v2] ){
		parent[v2] = v1;
	} else if( rank[v2] > rank[v1] ){
		parent[v1] = v2;
	} else {
		parent[v1] = v2;
		rank[v2]++;
	}
}

void Graph::makeSet( string v ){
	parent[v] = v;
	rank[v] = 0;
}

void Graph::shortestPath(){
	map<string, int> distance;
	map<string, bool> visited;
	
	for( vecSIt it = vertexs.begin(); it != vertexs.end(); ++it ){
		visited[*it] = false;
		distance[*it] = INT_MAX;
	}
	int index = 0;
	string current = vertexs[index];
	distance[current] = 0;
	visited[current] = true;
	pair<string, int> lowest = make_pair( current, INT_MAX );
	
	//go through all the node conected to current
	while( hasVisited( visited ) ){
		for( vecEIt it = edges.begin(); it != edges.end(); ++it ){
			string src = it->GetSource();
			string dest = it->GetDestination();
			if( src == current ){ //then get the weights
				int dw = distance[dest];
				int mw = distance[current];
				int ew = it->GetWeight();
				distance[dest] = min( dw, ( mw + ew )  );
				if( distance[dest] < lowest.second && !visited[dest] ){
					lowest.first = dest;
					lowest.second = distance[dest];
				}
			}
		}
		//set vertex visited and go to next one
		for( map<string, int>::iterator it = distance.begin(); it != distance.end(); ++it ){
			cout << "" << it->first << ":" << it->second << ", ";
		}
		cout << endl;
		visited[current] = true;
		current = lowest.first;
		lowest = make_pair( current, INT_MAX );
	}
	/*
	it->GetSource()
	it->GetDestination()
	it->GetWeight()
	*/
}

bool Graph::hasVisited(map<string,bool> visited){
	bool done = true;
	for( map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it ){
		if( !it->second ){
			done = false;
			break;
		}
	}
	return !done;
}

//string Graph::isVisited( map<string, bool> visited, string v ){
//	for( map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it ){
//		if( !it->second ){
//			return it->first;
//		}
//	}
//	return "";
//}
