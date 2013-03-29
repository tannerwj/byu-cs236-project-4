#pragma once
#include <stack>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include "Token.h"

class Parameter
{
public:
	Parameter(void);
	~Parameter(void);

	Parameter(std::stack<Token*>*);
	std::string getParameter(std::stack<Token*>*);
	std::string getExpression(std::stack<Token*>*);
	std::string getParameterList(std::stack<Token*>*);
	std::string getParameterListTail(std::stack<Token*>*);
	std::vector<Token> getAttributes();
	std::string toString();

private:
	std::string ParameterString;
	std::vector<Token> attributes;
	void failure(Token*);

	// <Parameter>  ->  <String> | <Identifier> | <Expression>
};

