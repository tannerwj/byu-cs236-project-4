#include "RuleList.h"
#include "Rule.h"
#include "Utils.h"
#include <iostream>

RuleList::RuleList(void){}
RuleList::~RuleList(void){}

RuleList::RuleList(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() != RULES){
		failure(currentToken);
	}
	
	tokens->pop();
	currentToken = tokens->top();
	if(currentToken->getTokenType() != COLON){
		failure(currentToken);
	}

	tokens->pop();
	RuleString = getRuleList(tokens);
}

//<Rule List>  ->  <Rule> <Rule List> | ех
std::string RuleList::getRuleList(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	if(currentType == ID){  //<Rule> <Rule list>

		Rule f = Rule(tokens);
		RuleVector.push_back(f);
		return "\n" + f.toString() + getRuleList(tokens);

	} else {
		return "";  // ех
	}
}
std::string RuleList::toString(){
	std::string str;
	return "\nRules(" + itoa(str,RuleVector.size()) + "):" + RuleString;
}

std::vector<Rule> RuleList::getRuleVector(){
	return RuleVector;
}

void RuleList::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}
