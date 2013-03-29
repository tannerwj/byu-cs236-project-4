#pragma once
#include <vector>
#include <set>
#include <iterator>
#include <string>
class Domain
{
public:
	Domain(void);
	~Domain(void);

	Domain(std::vector<std::string>);
	std::string toString();

private:
	std::string domainstring;
	std::set<std::string> domainset;
	std::set<std::string>::iterator iter;
};

