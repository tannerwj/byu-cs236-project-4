#pragma once
#include <stdlib.h>
#include <map>
#include "Relation.h"
#include "Fact.h"
#include "Scheme.h"
#include "Query.h"
#include "Rule.h"

class Database
{
public:
	Database(void);
	~Database(void);
	Database(std::vector<Scheme>, std::vector<Fact>, std::vector<Rule> , std::vector<Query>);
	void ProcessQuery(Query);
	bool ProcessRule(Rule);
	Relation ProcessPredicate(std::string, std::vector<Token>);
	std::string toString();
private:
	std::map<std::string, Relation> database;
	Token checkVariable(Token, std::vector<Token>);
};

