#pragma once
#include <stack>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include "Token.h"
#include "Parameter.h"
class Predicate
{
public:
	Predicate(void);
	~Predicate(void);
	Predicate(std::stack<Token*>*);
	Predicate(std::stack<Token*>*, bool);
	std::string getPredicate(std::stack<Token*>*);
	std::string getIdentifier(std::stack<Token*>*);
	std::string getPredicateList(std::stack<Token*>*);
	std::string getPredicateListTail(std::stack<Token*>*);
	std::string getName();
	std::vector<Token> getAttributes();
	std::string toString();
private:
	std::string PredicateString;
	std::string name;
	Parameter p;
	void failure(Token*);

};


