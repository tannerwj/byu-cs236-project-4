#pragma once
#include <string>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include "Token.h"

class Scheme
{
public:
	Scheme(void);
	~Scheme(void);
	Scheme(std::stack<Token*>*);
	std::string getScheme(std::stack<Token*>*);
	std::string getIdentifier(std::stack<Token*>*);
	std::string getIdentifierList(std::stack<Token*>*);
	std::string getIdentifierListTail(std::stack<Token*>*);
	std::string getName();
	std::vector<Token> getAttributes();
	std::string toString();
private:
	std::string id;
	std::string name;
	std::vector<Token> attributes;
	void failure(Token*);
	
};

