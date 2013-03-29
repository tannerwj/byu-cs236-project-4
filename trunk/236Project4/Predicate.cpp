#include "Predicate.h"
#include "Parameter.h"
#include <iostream>
#include <vector>


Predicate::Predicate(void){}
Predicate::~Predicate(void){}

Predicate::Predicate(std::stack<Token*>* tokens){
	PredicateString = getPredicateList(tokens);
}

Predicate::Predicate(std::stack<Token*>* tokens, bool){
	PredicateString = getPredicate(tokens);
}


// <Predicate>   ->  <Identifier> ( <Parameter List> )
std::string Predicate::getPredicate(std::stack<Token*>* tokens){

	name = getIdentifier(tokens);
	predicateNames.push_back(name);

	std::string s = name + "(";

	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() != LEFT_PAREN){
		failure(currentToken);
	}

	tokens->pop();
	
	p = Parameter(tokens);


	predicateAttributes.push_back(p.getAttributes());

	s += p.toString();
	currentToken = tokens->top();

	if(currentToken->getTokenType() != RIGHT_PAREN){
		failure(currentToken);
	}
	tokens->pop();

	return s + ")";

}

std::string Predicate::getIdentifier(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();
		
	if(currentToken->getTokenType() != ID){
		failure(currentToken);
	} 
	tokens->pop();

	return currentToken->getTokensValue();
}

// <Predicate List>  ->  <Predicate> <Predicate List Tail>
std::string Predicate::getPredicateList(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	if(currentType != ID)
		failure(currentToken);

	std::string s = getPredicate(tokens);
	return s + getPredicateListTail(tokens);
	
}

// <Predicate List Tail> ->  , <Predicate List> | ех
std::string Predicate::getPredicateListTail(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	if(currentType == COMMA){
		tokens->pop();
		return "," + getPredicateList(tokens);
	} else {
		return "";
	}

}

std::string Predicate::getName(){
	return name;
}

std::vector<Token> Predicate::getAttributes(){
	return p.getAttributes();
}

std::vector<std::string> Predicate::getPredicateNames(){
	return predicateNames;
}
std::vector<std::vector<Token>> Predicate::getPredicateAttributes(){
	return predicateAttributes;
}

std::string Predicate::toString(){
	//return PredicateString;
	return name + p.toString();
}

void Predicate::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}