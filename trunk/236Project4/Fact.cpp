#include "Fact.h"
#include <iostream>


Fact::Fact(void){}
Fact::~Fact(void){}

Fact::Fact(std::stack<Token*>* tokens){
	id = getFact(tokens);
}

std::string Fact::getFact(std::stack<Token*>* tokens){

	name = getIdentifier(tokens);

	std::string s = "  " + name + "(";
	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != LEFT_PAREN)
		failure(currentToken);

	tokens->pop();

	s += getConstantList(tokens);
	currentToken = tokens->top();

	if(currentToken->getTokenType() != RIGHT_PAREN)
		failure(currentToken);

	tokens->pop();
	currentToken = tokens->top();

	if(currentToken->getTokenType() != PERIOD)
		failure(currentToken);
	 else 
		tokens->pop();

	return s + ").";
}

std::string Fact::getIdentifier(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != ID)
		failure(currentToken);

	tokens->pop();

	return currentToken->getTokensValue();
}

//<Constant List>  ->  <String> <Constant List Tail>
std::string Fact::getConstantList(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != STRING){;
		failure(currentToken);
		return "";
	} else {
		attributes.push_back(new Token(currentToken));
		tokens->pop();
		return currentToken->getTokensValue() + getConstantListTail(tokens);
	}
}

//<Constant List Tail> ->  , <Constant List> | ех
std::string Fact::getConstantListTail(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() == COMMA){
		tokens->pop();
		currentToken = tokens->top();
		return "," + getConstantList(tokens);
	} else {
		return "";
	}

}

std::vector<Token> Fact::getAttributes(){
	return attributes;
}

std::string Fact::getName(){
	return name;
}

std::string Fact::toString(){
	//return id;
	std::string temp;
	temp += attributes[0].getTokensValue();
	int count;
	int s = attributes.size();
	for (count = 1; count < s; count++){
		temp += "," + attributes[count].getTokensValue();
	}
	
	return name + "("+ temp + ")";
}

void Fact::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}