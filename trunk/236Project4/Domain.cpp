#include "Domain.h"
#include "Utils.h"


Domain::Domain(void){}

Domain::~Domain(void){}

Domain::Domain(std::vector<std::string> d){

	std::copy( d.begin() , d.end() ,std::inserter(domainset, domainset.end()));

	for(iter = domainset.begin(); iter != domainset.end(); iter++){
		domainstring += "  " + *iter + "\n";
	}
}

std::string Domain::toString(){
	std::string str;
	return "\nDomain(" + itoa(str,domainset.size()) + "):\n"+ domainstring;
}
