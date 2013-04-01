#include "Database.h"
#include <iostream>



Database::Database(void){}
Database::~Database(void){}

Database::Database(std::vector<Scheme> s, std::vector<Fact> f, std::vector<Rule> r, std::vector<Query> q){

	std::vector<Scheme>::iterator it;
	std::vector<Fact>::iterator factIter;
	std::vector<Rule>::iterator ruleIter;
	std::vector<Query>::iterator queryIter;
	bool addedSomething;
	int ruleCounter = 0;		// Counts how many passes through the rules it takes to populate the databases

	
    for ( it = s.begin() ; it < s.end(); it++ )
		database[it->getName()] = Relation(it->getName(), it->getAttributes());
    
	for ( factIter = f.begin(); factIter < f.end(); factIter++)
		database[factIter->getName()].addTuple(*factIter);

	do {
		ruleCounter++;
		addedSomething = false;

		for ( ruleIter = r.begin(); ruleIter < r.end(); ruleIter++) {
			if(ProcessRule(*ruleIter))
				addedSomething = true;
		}
	} while (addedSomething);

	std::cout << "Schemes populated after " << ruleCounter << " passes through the Rules.\n";

	
	for ( queryIter = q.begin(); queryIter < q.end(); queryIter++)
		ProcessQuery(*queryIter);

}

void Database::ProcessQuery(Query q){

	std::vector<Token> ProjectTokens;
	std::vector<Tuple> SelectTuples;
	std::vector<Token> queryTokens = q.getAttributes();
	Relation r = Relation(database[q.getName()].Rename(q.getAttributes()));
	

	std::vector<Token>::iterator it;
	//int counter = 0;
	for(it = queryTokens.begin(); it < queryTokens.end(); it++){

		if(it->getTokenType() == STRING)
			SelectTuples.push_back(Tuple(r.getSchema(), q.getAttributes()));
		else 
			ProjectTokens.push_back(*it);

		//counter++;
	}

	for(int i = 0; i < SelectTuples.size(); i++)
		r = r.Select(SelectTuples[i]);
	

	if(ProjectTokens.size() != 0)
		r = r.Project(ProjectTokens);
	
	std::cout << q.toString();
	if(r.getTupleSet().getTuples().size() == 0)
		std::cout << " No\n";
	else
		std::cout << " Yes(" << r.getTupleSet().getTuples().size() << ")\n";


	if(ProjectTokens.size() != 0)
		std::cout << r.toString();
}

bool Database::ProcessRule(Rule r){
	
	Relation joinedPredicates = ProcessPredicate(r.getPredicateNames().at(0), r.getPredicatesAttributes().at(0));

	for(unsigned int i = 1; i < r.getPredicateNames().size(); i++){
			Relation temp = ProcessPredicate(r.getPredicateNames().at(i), r.getPredicatesAttributes().at(i));
			joinedPredicates = joinedPredicates.Join(temp);
	}

	joinedPredicates = joinedPredicates.Project(Schema(r.getHead().getAttributes()));

	return database[r.getHead().getName()].Union(joinedPredicates);						// returns true if something was added to the database

}

Relation Database::ProcessPredicate(std::string name, std::vector<Token> attributes){
	std::vector<Token> ProjectTokens;
	std::vector<Tuple> SelectTuples;
	Relation r = Relation(database[name].Rename(attributes));
	std::vector<Token>::iterator it;

	//int counter = 0;
	for(it = attributes.begin(); it < attributes.end(); it++){

		if(it->getTokenType() == STRING)
			SelectTuples.push_back(Tuple(r.getSchema(), attributes));
		else
			ProjectTokens.push_back(*it);

		//counter++;
	}

	for(int i = 0; i < SelectTuples.size(); i++)
		r = r.Select(SelectTuples[i]);
	
	if(ProjectTokens.size() != 0)
		r = r.Project(ProjectTokens);

	return r;

}


std::string Database::toString(){
	std::string temp;

	std::map<std::string, Relation>::iterator iter;

	  for(iter = database.begin(); iter != database.end(); iter++) {
		  temp += iter->second.toString() + "\n";
	  }

	return temp;
}
