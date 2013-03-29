#include "Schema.h"
#include <iostream>


Schema::Schema(std::vector<Token> values){
	std::vector<Token>::iterator it;
    for ( it = values.begin() ; it < values.end(); it++ ) {
		schema.push_back(*it);
    }
}

Schema::Schema(const Schema& sch){
	std::vector<Token> temp = sch.schema;
	std::vector<Token>::iterator it;
	for ( it = temp.begin() ; it < temp.end(); it++ ) {
		schema.push_back(*it);
    }
}

std::vector<Token> Schema::getSchemas(){
	return schema;
}

void Schema::add(Token t){
	schema.push_back(t);
}

bool Schema::contains(Token t){	
	if(schema.size() != 0){
		for(int i = 0; i < schema.size(); i++){
			if(schema[i].getTokensValue() == t.getTokensValue()){
				//std::cout << "Returning True\n";
				return true;
			}
		}
	}
	//std::cout << "Returning False!\n";
	return false;
}

Schema::Schema(void){}
Schema::~Schema(void){}
