#include "Parameter.h"
#include <iostream>


Parameter::Parameter(void){}
Parameter::~Parameter(void){}

Parameter::Parameter(std::stack<Token*>* tokens){
	ParameterString = getParameterList(tokens);
}


//<Parameter List>   ->  <Parameter> <Parameter List Tail>
std::string Parameter::getParameterList(std::stack<Token*>* tokens){

	std::string s = getParameter(tokens);
	return s + getParameterListTail(tokens);
}

//<Parameter>   ->  <String> | <Identifier> | <Expression>
std::string Parameter::getParameter(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	if(currentType == ID || currentType == STRING){
		attributes.push_back(new Token(currentToken));
		tokens->pop();
		return currentToken->getTokensValue();
	} else if (currentType == LEFT_PAREN){
		return getExpression(tokens);
	} else {
		failure(currentToken);
		return "";
	}
}

// <Parameter List Tail>  ->  , <Parameter List> | ех
std::string Parameter::getParameterListTail(std::stack<Token*>* tokens){
	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	if(currentToken->getTokenType() == COMMA){
		tokens->pop();
		return "," + getParameterList(tokens);
	} else {
		return "";
	}
}

// <Expression>  -> ( <Parameter> <Operator> <Parameter> )
std::string Parameter::getExpression(std::stack<Token*>* tokens){

	Token* currentToken = tokens->top();
	TokenType currentType = currentToken->getTokenType();

	std::string s = "(";

	tokens->pop();
	s += getParameter(tokens);


	currentToken = tokens->top();
	if(currentToken->getTokenType() == MULTIPLY || currentToken->getTokenType() == ADD){
		s += currentToken->getTokensValue();
	} else {
		failure(currentToken);
	}


	tokens->pop();
	currentToken = tokens->top();

	s += getParameter(tokens);

	currentToken = tokens->top();

	if(currentToken->getTokenType() != RIGHT_PAREN){
		failure(currentToken);
	}

	tokens->pop();
	return s + ")";
}

std::vector<Token> Parameter::getAttributes(){
	return attributes;
}

std::string Parameter::toString(){
	//return ParameterString;
	std::string temp;
	temp += attributes[0].getTokensValue();
	int count;
	int s = attributes.size();
	for (count = 1; count < s; count++){
		temp += "," + attributes[count].getTokensValue();
	}
	
	return "("+ temp + ")";
}

void Parameter::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}
