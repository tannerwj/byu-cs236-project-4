#include "State.h"

using namespace std;

string StateToString(State tokenType){
    string result = "";
    switch(tokenType){
        case Comma:                      result = "Comma"; break;
        case Period:                     result = "Period"; break;
		case Q_mark:                     result = "Q_mark"; break;
		case Left_Paren:				 result = "Left_Paren"; break;
		case Right_Paren:				 result = "Right_Paren"; break;
        case SawColon:                   result = "SawColon"; break;
        case Colon:		                 result = "Colon"; break;
		case Colon_Dash:                 result = "Colon_Dash"; break;
		case Multiply:                   result = "Multiply"; break;
		case Add:			             result = "Add"; break;
		case Schemes:					 result = "Schemes"; break;
		case Facts:						 result = "Facts"; break;
		case Rules:						 result = "Rules"; break;
		case Queries:					 result = "Queries"; break;
		case Id:						 result = "Id"; break;
        case SawAQuote:                  result = "SawAQuote"; break;
        case ProcessingString:           result = "ProcessingString"; break;
        case PossibleEndOfString:        result = "PossibleEndOfString"; break;
		case SawId:						 result = "SawId"; break;
		case WhiteSpace:				 result = "WhiteSpace"; break;
		case SawComment:				 result = "SawComment"; break;
		case ProcessingLineComment:		 result = "ProcessingLineComment"; break;
		case ProcessingBlockComment:	 result = "ProcessingBlockComment"; break;
		case PossibleEndOfComment:		 result = "PossibleEndOfComment"; break;
		case Undefined:					 result = "Undefined"; break;
        case Start:                      result = "Start"; break;
        case End:                        result = "End"; break;
    }
    return result;
};
