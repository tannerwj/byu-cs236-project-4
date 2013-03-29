#include "FactList.h"
#include "Utils.h"
#include <iostream>


FactList::FactList(void){}


FactList::~FactList(void){}

FactList::FactList(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() != FACTS){
		failure(currentToken);
	}
	
	tokens->pop();
	currentToken = tokens->top();
	if(currentToken->getTokenType() != COLON){
		failure(currentToken);
	}

	tokens->pop();
	FactString = getFactList(tokens);
}

std::string FactList::getFactList(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	if(currentType == ID){

		Fact f = Fact(tokens);
		FactVector.push_back(f);
		//std::cout << f.toString();
		return "\n" + f.toString() + getFactList(tokens);

	} else {
		return "";
	}

}

std::string FactList::toString(){
	std::string str;
	return "\nFacts(" + itoa(str,FactVector.size()) + "):" + FactString;
}

std::vector<Fact> FactList::getFactVector(){
	return FactVector;
}

void FactList::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}
