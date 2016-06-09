/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Edge.h
 * Author: michael
 *
 * Created on June 8, 2016, 5:06 PM
 */

#ifndef EDGE_H
#define EDGE_H

#include <string>

using namespace std;

class Edge {
private:
	string source;
	string destination;
	int weight;
public:
	Edge( string src, int weight, string dest ){
		source = src;
		this->weight = weight;
		destination = dest;
	}

    void SetWeight(int weight) {
    	this->weight = weight;
    }

    int GetWeight() const {
    	return weight;
    }

    void SetDestination(string destination) {
    	this->destination = destination;
    }

    string GetDestination() const {
    	return destination;
    }

    void SetSource(string source) {
    	this->source = source;
    }

    string GetSource() const {
    	return source;
    }
	
	bool operator < (const Edge& right) const  {
        return ( weight < right.weight );
    }
	
	
};


#endif /* EDGE_H */

