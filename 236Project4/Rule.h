#pragma once
#include <string>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include "Token.h"
#include "Predicate.h"

class Rule
{
public:
	Rule(void);
	~Rule(void);
	Rule(std::stack<Token*>*);
	std::string getRule(std::stack<Token*>*);
	std::string getHeadPredicate(std::stack<Token*>*);
	std::string getIdentifier(std::stack<Token*>*);
	std::string getIdentifierList(std::stack<Token*>*);
	std::string getIdentifierListTail(std::stack<Token*>*);
	std::string getPredicateList(std::stack<Token*>*);
	Predicate getHead();
	std::vector<std::string> getPredicateNames();
	std::vector<std::vector<Token>> getPredicatesAttributes();
	std::string toString();
private:
	std::string RuleString;
	Predicate headPredicate;
	Predicate predicateList;
	void failure(Token*);

};


