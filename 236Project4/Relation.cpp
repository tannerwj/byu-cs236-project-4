#include "Relation.h"
#include <iostream>


Relation::Relation(){}
Relation::~Relation(){}

Relation::Relation(std::string st, std::vector<Token> v){
	name = st;
	s = Schema(v);
}

Relation::Relation(const Relation& r) {
	name = r.name;
	s = Schema(r.s); 
	t = TupleSet(r.t);
}

void Relation::addTuple(Fact f){
	t.addTuple(s.getSchemas(), f);
}

void Relation::addTuple(std::vector<Token> v){
	t.addTuple(s.getSchemas(), v);
}

Relation Relation::Rename(Schema q){

	Relation temp = Relation(name, q.getSchemas());
	std::vector<Tuple> myTuples = t.getTuples();
	std::vector<Tuple>::iterator it;
	
	for ( it = myTuples.begin(); it < myTuples.end(); it++) {
		temp.addTuple(it->getValues());
	}

	return temp;
}

Relation Relation::Project(Schema schema){

	Schema p;
	for(int i = 0; i < schema.getSchemas().size(); i++){
		if(!p.contains(schema.getSchemas().at(i)))
			p.add(schema.getSchemas().at(i));
	}	

	Relation temp = Relation(name, p.getSchemas());

	std::vector<Tuple> myTuples = t.getTuples();
	std::vector<Tuple>::iterator it;
	std::vector<Token> tempVec;
	bool canPro, canAdd;

	for(it = myTuples.begin(); it < myTuples.end(); it++){
		std::vector<Token> newAttributes;
		canAdd = true;

		for(int index = 0; index < p.getSchemas().size(); index++){

			canPro = true;
			tempVec = it->getValue(p.getSchemas().at(index));
			for(int i = 1; i < tempVec.size(); i++){
				if(tempVec.at(0).getTokensValue() != tempVec.at(i).getTokensValue())
					canPro = false;
			}
			if(!canPro)
				canAdd = false;		
			if(canPro){
				newAttributes.push_back(tempVec.at(0));
			}	
		}
		if(newAttributes.size() > 0 && canAdd)
			temp.addTuple(newAttributes);
	}

	return temp;
}

Relation Relation::Select(Tuple xTuple){

	Relation temp = Relation(name, s.getSchemas());
	std::vector<Tuple> myTuples = t.getTuples();
	std::vector<Tuple>::iterator it;
	
	for ( it = myTuples.begin(); it < myTuples.end(); it++) {
		std::vector<Token>::iterator tokenIter;
		std::vector<Token> tokenCounter = it->getValues();
		bool canSelect = false;
		int index = 0;

		for ( tokenIter = tokenCounter.begin(); tokenIter < tokenCounter.end(); tokenIter++){
			if(xTuple.getValues().at(index).getTokenType() == STRING){
				if( xTuple.getValues().at(index).getTokensValue() == it->getValues().at(index).getTokensValue()){
					canSelect = true;
				} else {
					canSelect = false;
					break;
				}
			}

		index++;
		}
		if(canSelect)
			temp.addTuple(it->getValues());		
	}

	return temp;
}

Relation Relation::Join(Relation r){
	return Relation();
}
void Relation::Union(Relation r){

	std::vector<Tuple> tuples = r.getTupleSet().getTuples();
	std::vector<Tuple>::iterator it;

	for(it = tuples.begin(); it < tuples.end(); it++){
		addTuple(it->getValues());
	}

}

std::vector<Token> Relation::getSchema(){
	return s.getSchemas();
}

TupleSet Relation::getTupleSet(){
	return t;
}

std::string Relation::toString(){
	
	std::string temp;
	temp += t.toString();

	return temp;
}

