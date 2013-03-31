#pragma once
#include <vector>
#include <set>
#include "Token.h"
#include "Tuple.h"
#include "Fact.h"

class TupleSet
{
public:
	TupleSet(void);
	~TupleSet(void);
	TupleSet(const TupleSet&);
	void addTuple(std::vector<Token>, Fact);
	bool addTuple(std::vector<Token>, std::vector<Token>);
	std::vector<Tuple> getTuples();
	std::string toString();
private:
	std::set<Tuple> tuples;
	bool testDuplicate(std::vector<Token>);
};