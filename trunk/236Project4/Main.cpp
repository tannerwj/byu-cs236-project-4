#include "Lex.h"
#include "Utils.h"
#include "DatalogProgram.h"
#include <iostream>

int main(int argc, char* argv[]) {

    Lex lex(argv[1]);
	//Lex lex("test.txt");
	// This is a new comment
	std::vector<Token *>* tokens = lex.getVector();
	
	DatalogProgram Datalog = DatalogProgram(tokens);
	
    return 0;
}

