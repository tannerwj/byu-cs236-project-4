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
	std::vector<std::string> getPredicateNames();
	std::vector<std::vector<Token>> getPredicateAttributes();
	std::string toString();
private:
	std::string PredicateString;
	std::vector<std::string> predicateNames;
	std::vector<std::vector<Token>> predicateAttributes;
	std::string name;
	Parameter p;
	void failure(Token*);

};


