#include "Tuple.h"
#include <iostream>

Tuple::Tuple(std::vector<Token> n, std::vector<Token> v){

	std::vector<Token>::iterator it;

	for (it = n.begin() ; it < n.end(); it++)
		names.push_back(*it);
	
	for (it = v.begin() ; it < v.end(); it++)
		values.push_back(*it);
	
}

Tuple::~Tuple(void){}

std::vector<Token> Tuple::getValue(Token t){
	std::vector<Token> temp;
	for(int i = 0; i < names.size(); i++){
		
		if(names.at(i).getTokensValue() == t.getTokensValue())
			temp.push_back(values.at(i));
			
	}
	return temp;
}

std::vector<Token> Tuple::getValues(){
	return values;
}

std::vector<Token> Tuple::getNames(){
	return names;
}

std::string Tuple::toString(){
	std::string temp;
	if(values.size() > 0){
		temp += names[0].getTokensValue() + "=" + values[0].getTokensValue();
		int count;
		int s = values.size();
		for (count = 1; count < s; count++){
			temp += ", " + names[count].getTokensValue() + "=" + values[count].getTokensValue();
		}
		return "  " + temp + "\n";
	}
	return "";
}

bool operator==(const Tuple& left, const Tuple& right){

	if(left.values.size() == 0 || right.values.size() == 0)
		return false;

	if (left.names.size() != right.names.size())
		return false;

	for(int i = 0; i < left.names.size(); i++){
		if (left.values[i].getTokensValue() != right.values[i].getTokensValue())
			return false;
	}
    return true;
}

bool operator!=(const Tuple& left, const Tuple& right){
	return !(left == right);
}

bool operator < (const Tuple& left, const Tuple& right){

	if(left.values.size() == 0 || right.values.size() == 0)
		return false;

	int i = 0;
	while( i < right.values.size() - 1 && i < left.values.size() - 1 && left.values[i].getTokensValue() == right.values[i].getTokensValue()){
			i++;
	}

	return left.values[i].getTokensValue() < right.values[i].getTokensValue();
}

bool operator>(const Tuple& left, const Tuple& right){
	return !(left < right);
}
