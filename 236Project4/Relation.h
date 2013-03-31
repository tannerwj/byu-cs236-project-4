#pragma once
#include "Schema.h"
#include "Tuple.h"
#include "Token.h"
#include "TupleSet.h"
#include <vector>

class Relation
{
public:
	Relation();
	~Relation();

	Relation(std::string, std::vector<Token>);
	Relation(const Relation&);
	std::string toString();
	void addTuple(Fact);
	bool addTuple(std::vector<Token>);
	Relation Rename(Schema);
	Relation Rename(Token);
	Relation Project(Schema);
	Relation Select(Tuple);
	Relation Join(Relation);
	bool Union(Relation);
	std::vector<Token> getSchema();
	TupleSet getTupleSet();

private:
	std::string name;
	Schema s;
	TupleSet t;
};

