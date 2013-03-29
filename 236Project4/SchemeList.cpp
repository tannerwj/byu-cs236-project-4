#include "SchemeList.h"
#include "Token.h"
#include "TokenType.h"
#include <iostream>
#include "Utils.h"


SchemeList::SchemeList(void)
{
}

SchemeList::SchemeList(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() != SCHEMES){
		failure(currentToken);
	}
	
	tokens->pop();
	currentToken = tokens->top();
	if(currentToken->getTokenType() != COLON){
		failure(currentToken);
	}

	tokens->pop();
	SchemeString = getSchemeList(tokens);
	
}

//<Scheme List> ->  <Scheme> <Scheme List Tail> 
std::string SchemeList::getSchemeList(std::stack<Token*>* tokens){
	Scheme s = Scheme(tokens);
	SchemeVector.push_back(s);
	return s.toString() + getSchemeListTail(tokens);
}

//<Scheme List Tail>   ->  <Scheme List> | ех
std::string SchemeList::getSchemeListTail(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	if(tokens->size() == 0){
		failure(currentToken);
	} else if(currentType == END){
		failure(currentToken);
	}else if(currentType == ID){
		return "\n" + getSchemeList(tokens);
	} else {
		return "";
	}

}

std::string SchemeList::toString(){
	std::string str;
	return "Schemes(" + itoa(str,SchemeVector.size()) + "):\n" + SchemeString;
}

std::vector<Scheme> SchemeList::getSchemeVector() {
	return SchemeVector;
}

void SchemeList::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}

SchemeList::~SchemeList(void)
{
}
