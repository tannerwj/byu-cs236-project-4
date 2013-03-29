#pragma once
#include "Token.h"
#include <vector>

class Schema
{
public:
	Schema(std::vector<Token>);
	Schema(const Schema&);
	Schema(void);
	~Schema(void);
	std::vector<Token> getSchemas();
	bool contains(Token);
	void add(Token);
	
private:
	std::vector<Token> schema;
};

