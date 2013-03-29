#include "Database.h"
#include <iostream>



Database::Database(void){}
Database::~Database(void){}

Database::Database(std::vector<Scheme> s, std::vector<Fact> f, std::vector<Rule> r, std::vector<Query> q){

	std::vector<Scheme>::iterator it;
    for ( it = s.begin() ; it < s.end(); it++ ) {
		database[it->getName()] = Relation(it->getName(), it->getAttributes());
    }

	std::vector<Fact>::iterator factIter;
	for ( factIter = f.begin(); factIter < f.end(); factIter++) {
		database[factIter->getName()].addTuple(*factIter);
	}

	//std::vector<Rule>::iterator ruleIter;
	//for ( factIter = r.begin(); ruleIter < r.end(); ruleIter++) {
	//	;
	//}

	std::vector<Query>::iterator queryIter;
	for ( queryIter = q.begin(); queryIter < q.end(); queryIter++) {
		ProcessQuery(*queryIter);
	}
	

}

void Database::ProcessQuery(Query q){

	std::vector<Token> ProjectTokens;
	std::vector<Tuple> SelectTuples;
	std::vector<Token> queryTokens = q.getAttributes();
	Relation r = Relation(database[q.getName()].Rename(q.getAttributes()));
	

	std::vector<Token>::iterator it;
	int counter = 0;
	for(it = queryTokens.begin(); it < queryTokens.end(); it++){
		if(it->getTokenType() == STRING){
			SelectTuples.push_back(Tuple(r.getSchema(), q.getAttributes()));
		} else {
			ProjectTokens.push_back(*it);
			//r = r.rename(schema.get(i), qValues.get(i));
		}
		counter++;
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


std::string Database::toString(){
	std::string temp;

	std::map<std::string, Relation>::iterator iter;

	  for(iter = database.begin(); iter != database.end(); iter++) {
		  temp += iter->second.toString() + "\n";
	  }

	return temp;
}
