#include "DatalogProgram.h"
#include <stack>
#include <iostream>


DatalogProgram::DatalogProgram(std::vector<Token *>* tokens){

	std::stack<Token *> tokenStack;

    while(tokens->size() > 0) {
		int index = tokens->size() - 1;
        Token* token = (*tokens)[index];
		tokenStack.push(token);
		
		if(token->getTokenType() == STRING){
			domainVector.push_back(token->getTokensValue());
		}

		tokens->pop_back();
    }

	schemes = SchemeList(&tokenStack);
	facts = FactList(&tokenStack);
	rules = RuleList(&tokenStack);
	queries = QueryList(&tokenStack);
	domain = Domain(domainVector);
	
	Token* currentToken = tokenStack.top();
	
	if(currentToken->getTokenType() != END)
		failure(currentToken);

	db = Database(schemes.getSchemeVector(), facts.getFactVector(), rules.getRuleVector(), queries.getQueryVector());

}

std::string DatalogProgram::toString(){
	return "Success!\n" + schemes.toString() + facts.toString() + rules.toString() + queries.toString() + domain.toString();
}

void DatalogProgram::failure(Token* t){
	std::cout << "Failure!\n  " + t->toString();
	exit(0);
}