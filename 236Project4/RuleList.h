#pragma once
#include <stack>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include "Rule.h"
#include "Token.h"


class RuleList
{
public:
	RuleList(void);
	~RuleList(void);
	RuleList(std::stack<Token*>*);
	std::string getRuleList(std::stack<Token*>*);
	std::string toString();
	std::vector<Rule> getRuleVector();

private:
	std::string RuleString;
	std::vector<Rule> RuleVector;
	void failure(Token*);

};


