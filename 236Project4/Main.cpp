#include "Lex.h"
#include "Utils.h"
#include "DatalogProgram.h"
#include <iostream>

int main(int argc, char* argv[]) {

    Lex lex(argv[1]);
	//Lex lex("test.txt");
	std::vector<Token *>* tokens = lex.getVector();
	
	DatalogProgram Datalog = DatalogProgram(tokens);
	
    return 0;
}
