#include "Scheme.h"
#include <iostream>


Scheme::Scheme(void){}
Scheme::~Scheme(void){}

Scheme::Scheme(std::stack<Token*>* tokens){
	id = getScheme(tokens);
}

//<Scheme>  ->  <Identifier> ( <Identifier List> )
std::string Scheme::getScheme(std::stack<Token*>* tokens){

	name = getIdentifier(tokens);

	std::string s = "  " + name + "(";

	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() != LEFT_PAREN){
		failure(currentToken);
	}

	tokens->pop();
	s += getIdentifierList(tokens);

	currentToken = tokens->top();

	if(currentToken->getTokenType() != RIGHT_PAREN){
		failure(currentToken);
	}

	tokens->pop();
	return s + ")";

}

std::string Scheme::getIdentifier(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() != ID){
		failure(currentToken);
	} 
	tokens->pop();

	return currentToken->getTokensValue();

}

//<Identifier List> ->  <Identifier> <Identifier List Tail>
std::string Scheme::getIdentifierList(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != ID){
		failure(currentToken);
	}

	attributes.push_back(new Token(currentToken));
	std::string str = getIdentifier(tokens);

	return str + getIdentifierListTail(tokens);
}

//<Identifier List Tail> ->  , <Identifier List> | ех
std::string Scheme::getIdentifierListTail(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() == COMMA){
		tokens->pop();
		return  "," + getIdentifierList(tokens);
	} else {
		return "";
	}
}

std::string Scheme::getName(){
	return name;
}
std::vector<Token> Scheme::getAttributes(){
	return attributes;
}

std::string Scheme::toString(){
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

void Scheme::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}