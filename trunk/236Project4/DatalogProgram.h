#pragma once
#include <vector>
#include "FactList.h"
#include "SchemeList.h"
#include "QueryList.h"
#include "RuleList.h"
#include "Domain.h"
#include "Token.h"
#include "Database.h"


class DatalogProgram
{
public:
	DatalogProgram(std::vector<Token *>*);
	std::string toString();

private:
	std::vector<std::string> domainVector;
	SchemeList schemes;
	FactList facts;
	RuleList rules;
	QueryList queries;
	Domain domain;
	Database db;
	
	void makeRelations(std::vector<Scheme>);
	void failure(Token*);
};

