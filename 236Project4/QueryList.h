#pragma once
#include <stack>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include "Query.h"
#include "Token.h"
class QueryList
{
public:
	QueryList(void);
	~QueryList(void);
	QueryList(std::stack<Token*>*);
	std::string getQueryList(std::stack<Token*>*);
	std::string getQueryListTail(std::stack<Token*>*);
	std::string toString();
	std::vector<Query> getQueryVector();

private:
	std::string QueryString;
	std::vector<Query> QueryVector;
	void failure(Token* t);
};

