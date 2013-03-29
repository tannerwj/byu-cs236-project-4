#include "Rule.h"
#include "Predicate.h"
#include <iostream>


Rule::Rule(void){}
Rule::~Rule(void){}

Rule::Rule(std::stack<Token*>* tokens){
	RuleString = getRule(tokens);
}

//<Rule>  ->  <Head Predicate> :- <Predicate List>.
std::string Rule::getRule(std::stack<Token*>* tokens){
	std::string s = "  " + getHeadPredicate(tokens) + " :- ";

	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != COLON_DASH){
		failure(currentToken);
	}

	tokens->pop();

	currentToken = tokens->top();

	predicateList = Predicate(tokens);

	currentToken = tokens->top();

	s += predicateList.toString();	

	if(currentToken->getTokenType() != PERIOD){
		failure(currentToken);
	} else {
		tokens->pop();
	}
	return s + ".";
}

//<Head Predicate>  ->  <Identifier> ( <Identifier List> )
std::string Rule::getHeadPredicate(std::stack<Token*>* tokens){

	headPredicate = Predicate(tokens, true);
	return headPredicate.toString();

}

std::string Rule::getIdentifier(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() != ID){
		failure(currentToken);
	} 
	tokens->pop();

	return currentToken->getTokensValue();

}
std::string Rule::getIdentifierList(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();

	if(currentToken->getTokenType() != ID){
		failure(currentToken);
	}

	std::string str = getIdentifier(tokens);

	return str + getIdentifierListTail(tokens);
}

std::string Rule::getIdentifierListTail(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	if(currentToken->getTokenType() == COMMA){
		tokens->pop();
		return  "," + getIdentifierList(tokens);
	} else {
		return "";
	}
}

Predicate Rule::getHead(){
	return headPredicate;
}

std::vector<std::string> Rule::getPredicateNames(){
	return predicateList.getPredicateNames();
}

std::vector<std::vector<Token>> Rule::getPredicatesAttributes(){
	return predicateList.getPredicateAttributes();
}

std::string Rule::toString(){
	return RuleString;
}
void Rule::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}


