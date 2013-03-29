#pragma once
#include <vector>
#include "Token.h"
class Tuple
{

private:
	Token name;
public:
	Tuple(void);
	Tuple(std::vector<Token>, std::vector<Token>);
	~Tuple(void);

	std::vector<Token> getValue(Token);
	std::vector<Token> names;
	std::vector<Token> values;
	std::vector<Token> getValues();	
	std::vector<Token> getNames();
	std::string toString();

	friend bool operator==(Tuple &left, Tuple &right);
	friend bool operator!=(Tuple &left, Tuple &right);
	friend bool operator<(const Tuple &left, const Tuple &right);
	friend bool operator>(Tuple &left, Tuple &right);

};

