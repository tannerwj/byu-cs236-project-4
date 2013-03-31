#include "TupleSet.h"
#include <iostream>


TupleSet::TupleSet(){}
TupleSet::~TupleSet(){}

TupleSet::TupleSet(const TupleSet& t){
	std::set<Tuple>::iterator it;
	std::set<Tuple> temp = t.tuples;

	for(it = temp.begin(); it != temp.end(); it++) 
		  tuples.insert(*it);
}

void TupleSet::addTuple(std::vector<Token> n, Fact f){
	tuples.insert(Tuple(n, f.getAttributes()));
}

bool TupleSet::addTuple(std::vector<Token> n, std::vector<Token> f){
	std::pair<std::set<Tuple>::iterator, bool> temp;
	temp = tuples.insert(Tuple(n, f));
	return temp.second;
}

std::vector<Tuple> TupleSet::getTuples(){
	std::set<Tuple>::iterator it;
	std::vector<Tuple> temp;

	for(it = tuples.begin(); it != tuples.end(); it++) 
		  temp.push_back(*it);

	return temp;
}

std::string TupleSet::toString(){

	std::set<Tuple>::iterator it;
	std::string temp;
	for ( it = tuples.begin(); it != tuples.end(); it++) {
		Tuple t = *it;
		temp += t.toString();
		
	}

	return temp;
}


