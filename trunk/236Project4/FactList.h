#pragma once
#include <string>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include "Token.h"
#include "Fact.h"

class FactList
{
public:
	FactList(void);
	~FactList(void);
	FactList(std::stack<Token*>*);
	std::string getFactList(std::stack<Token*>*);
	std::string getFact(std::stack<Token*>*);
	std::string toString();
	std::vector<Fact> getFactVector();
private:
	std::vector<Fact> FactVector;
	std::string FactString;
	void failure(Token*);
};

