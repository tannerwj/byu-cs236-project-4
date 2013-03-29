#pragma once
#include <stack>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include "Token.h"
#include "Predicate.h"
class Query
{
public:
	Query(std::stack<Token*>*);
	std::string getQuery(std::stack<Token*>*);
	std::string getName();
	std::vector<Token> getAttributes();
	std::string toString();

private:
	std::string id;
	Predicate p;
	void failure(Token*);
};

