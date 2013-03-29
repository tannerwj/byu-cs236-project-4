#include "Query.h"
#include "Predicate.h"
#include <iostream>


Query::Query(std::stack<Token*>* tokens){
	id = getQuery(tokens);
}

// <Query>  ->  <Predicate> ?
std::string Query::getQuery(std::stack<Token*>* tokens){

	p = Predicate(tokens, true);
	
	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != Q_MARK)
		failure(currentToken);

	tokens->pop();
	return "  " + p.toString() + "?";
}

std::string Query::getName(){
	return p.getName();
}

std::vector<Token> Query::getAttributes(){
	return p.getAttributes();
}

std::string Query::toString(){
	//return id;
	return p.toString() + "?";
}

void Query::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}
