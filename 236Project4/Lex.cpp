#include "Lex.h"

#include "Input.h"
#include "TokenType.h"
#include "Utils.h"
#include <iostream>
#include <ctype.h>

using namespace std;


Lex::Lex() {
	input = new Input();
    generateTokens(input);
}

Lex::Lex(const char* filename) {
    input = new Input(filename);
    generateTokens(input);
}

Lex::Lex(istream& istream) {
    input = new Input(istream);
    generateTokens(input);
}

Lex::Lex(const Lex& lex) {
    input = new Input(*lex.input);
    tokens = new vector<Token*>();

    vector<Token*>::iterator iter;
    for(iter=lex.tokens->begin(); iter != lex.tokens->end(); iter++) {
        Token* newToken = new Token(**iter);
        tokens->push_back(newToken);
    }

    index = lex.index;
    state = lex.state;
}


Lex::~Lex(){
    for (int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
    }
    delete tokens;
    delete input;
}

bool Lex::operator==(const Lex& lex) {
    bool result = (tokens->size() == lex.tokens->size()) && (index == lex.index);
    if(result) {
        vector<Token*>::iterator iter1;
        vector<Token*>::iterator iter2;
        iter1 = tokens->begin();
        iter2 = lex.tokens->begin();
        while(result && iter1 != tokens->end() && iter2 != lex.tokens->end()) {
            result = **iter1 == **iter2;
            iter1++;
            iter2++;
        }
        result = result && iter1 == tokens->end() && iter2 == lex.tokens->end();
    }
    return result;
}

string Lex::toString() const {
    int count = 0;
    string result;
    while(count < tokens->size()) {
        Token* token = (*tokens)[count];
        result += token->toString();
        count++;
    }
    result += "\nTotal Tokens = ";
    string countToString;
    result += itoa(countToString, count);
    result += "\n";
    return result;
}

void Lex::generateTokens(Input* input) {
    tokens = new vector<Token*>();
    index = 0;

    state = Start;
    while(state != End) {
        state = nextState();
    }
}

Token* Lex::getCurrentToken() {
    return (*tokens)[index];
}

 vector<Token *>* Lex::getVector(){
	return tokens;
 }

void Lex::advance() {
    index++;
}

bool Lex::hasNext() {
    return index < tokens->size();
}

State Lex::nextState() {
    State result;
    char character;
    switch(state) {
        case Start:               result = getNextState(); break;
        case Comma:               emit(COMMA); result = getNextState(); break;
        case Period:              emit(PERIOD); result = getNextState(); break;
		case Q_mark:              emit(Q_MARK); result = getNextState(); break;
		case Left_Paren:          emit(LEFT_PAREN); result = getNextState(); break;
		case Right_Paren:         emit(RIGHT_PAREN); result = getNextState(); break;
		case Colon_Dash:          emit(COLON_DASH); result = getNextState(); break;
		case Multiply:            emit(MULTIPLY); result = getNextState(); break;
		case Add:				  emit(ADD); result = getNextState(); break;
		case WhiteSpace:		  emit(WHITESPACE); result = getNextState(); break;
		case Undefined:           emit(UNDEFINED); result = getNextState(); break;

        case SawColon:
            character = input->getCurrentCharacter();
            if(character == '-') {
                result = Colon_Dash;
                input->advance();
            } else { //Every other character
                emit(COLON); result = getNextState();
            }
            break;
 
        case SawAQuote:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;

        case ProcessingString:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
				result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;

        case PossibleEndOfString:
            if(input->getCurrentCharacter() == '\'') {
                input->advance();
                result = ProcessingString;
            } else { //Every other character
                emit(STRING);
                result = getNextState();
            }
            break;

		case SawId:
			character = input->getCurrentCharacter();
			
			if (isalpha(character) || isdigit(character)){					// Stops processing the ID if the next character
				result = SawId;												// isn't a letter / number
				input->advance();
			} else {
				emit(ID); 
				result = getNextState();
			}
            
            break;

		case SawComment:
			character = input->getCurrentCharacter();

			if(character == '|'){											// Checks to see if it is a block/line comment
				result = ProcessingBlockComment;							// and processes the comment accordingly
			} else {
				result = ProcessingLineComment;
			}

			break;

		case ProcessingLineComment:
			character = input->getCurrentCharacter();

			if(character == '\n' || character == -1){						// Continues processing the line comment as
				//emit(COMMENT);												// long as it hasn't reached a new line or the
				result = getNextState();									// end of the file
			} else {
				result = ProcessingLineComment;
				input->advance();
			}
			break;

		case ProcessingBlockComment:
			character = input->getCurrentCharacter();

			if(character == '|'){											// Processes the block comment until if finds
				result = PossibleEndOfComment;								// the | character. Saves an Undefined token
			} else if(character == -1){										// if it reaches EOF before closing the comment
				emit(UNDEFINED);
				result = getNextState();
			} else {
				result = ProcessingBlockComment;
			}

			input->advance();
			break;

		case PossibleEndOfComment:
			if(input->getCurrentCharacter() == '#'){						// Saves Comment token if the character after '|'
				input->advance();											// is '#' If not it continues to process the comment
				//emit(COMMENT);
				result = getNextState();
			} else {
				result = ProcessingBlockComment;
			}
			break;
    };
    return result;
}

State Lex::getNextState() {
    State result;
    char currentCharacter = input->getCurrentCharacter();

    //The handling of checking for whitespace and setting the result to Whilespace and
    //checking for letters and setting the result to Id will probably best be handled by
    //if statements rather then the switch statement.

	 if(currentCharacter == -1){
		emit(END);								// Initially the getNextState() function checks 
		result = End;							// if it has reached the end of the file, ignores
	} else if(isspace(currentCharacter)){		// whitespace and checks for ID's
		result = WhiteSpace;

	} else if (isalpha(currentCharacter)){
		result = SawId;

	} else {

		switch(currentCharacter) {
			case ','  : result = Comma; break;
			case '.'  : result = Period; break;
			case '?'  : result = Q_mark; break;
			case '('  : result = Left_Paren; break;
			case ')'  : result = Right_Paren; break;
			case '*'  : result = Multiply; break;
			case '+'  : result = Add; break;
			case ':'  : result = SawColon; break;
			case '\'' : result = ProcessingString; break;
			case '#'  : result = SawComment; break;
			default   : result = Undefined; break;				//Any character not recognized as any of the Tokens will be saved as an Undefined Token

		}

	}


    input->advance();
    return result;
}

void Lex::emit(TokenType tokenType) {
    Token* token = new Token(tokenType, input->getTokensValue(), input->getCurrentTokensLineNumber());
    storeToken(token);
    input->mark();
}

void Lex::storeToken(Token* token) {

    //This section should ignore whitespace and comments and change the token type to the appropriate value
    //if the value of the token is "Schemes", "Facts", "Rules", or "Queries".

	string value = token->getTokensValue();
	TokenType type = token->getTokenType();

	if(type == ID){						//Checks for Keywords

		if(value == "Schemes")
			token->setTokenType(SCHEMES);
		else if(value == "Facts")
			token->setTokenType(FACTS);
		else if(value == "Rules")
			token->setTokenType(RULES);
		else if(value == "Queries")
			token->setTokenType(QUERIES);

	}

	if(type != WHITESPACE){				 //Whitespace tokens are ignored
		tokens->push_back(token);
	}
}