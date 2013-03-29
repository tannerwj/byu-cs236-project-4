#pragma once
#include <stack>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include "Token.h"
#include "Scheme.h"

class SchemeList
{
public:
	SchemeList(void);
	~SchemeList(void);
	SchemeList(std::stack<Token*>*);
	std::string getSchemeList(std::stack<Token*>*);
	std::string getSchemeListTail(std::stack<Token*>*);
	std::string toString();
	std::vector<Scheme> getSchemeVector();
private:
	std::vector<Scheme> SchemeVector;
	std::string SchemeString;
	void failure(Token*);
};

