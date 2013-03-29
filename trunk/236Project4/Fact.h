#pragma once
#include <stack>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include "Token.h"
class Fact
{
public:
	Fact(void);
	~Fact(void);
	Fact(std::stack<Token*>*);
	std::string getFact(std::stack<Token*>*);
	std::string getIdentifier(std::stack<Token*>*);
	std::string getConstantList(std::stack<Token*>*);
	std::string getConstantListTail(std::stack<Token*>*);
	std::vector<Token> getAttributes();
	std::string getName();
	std::string toString();
private:
	std::string id;
	std::string name;
	std::vector<Token> attributes;
	void failure(Token*);
};

