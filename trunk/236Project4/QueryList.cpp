#include "QueryList.h"
#include "Predicate.h"
#include "Query.h"
#include "Utils.h"
#include <iostream>


// <Query>  ->  <Predicate> ?

QueryList::QueryList(void){}
QueryList::~QueryList(void){}

QueryList::QueryList(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != QUERIES){
		failure(currentToken);
	}
	
	tokens->pop();
	currentToken = tokens->top();
	if(currentToken->getTokenType() != COLON){
		failure(currentToken);
	}

	tokens->pop();
	QueryString = getQueryList(tokens);
}

// <Query List>   ->  <Query> <Query List Tail>
std::string QueryList::getQueryList(std::stack<Token*>* tokens){

	Query q = Query(tokens);
	QueryVector.push_back(q);
	return q.toString() + getQueryListTail(tokens);

}

// <Query List Tail> ->  <Query List> | ех
std::string QueryList::getQueryListTail(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();

	TokenType currentType = currentToken->getTokenType();

	if(currentType == ID){
		return "\n" + getQueryList(tokens);
	} else {
		return "";
	}


}


std::string QueryList::toString(){
	std::string str;
	return "\nQueries(" + itoa(str,QueryVector.size()) + "):\n" + QueryString;
}

std::vector<Query> QueryList::getQueryVector(){
	return QueryVector;
}

void QueryList::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}
