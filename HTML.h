#pragma once
#include <string>
class HTML
{
private:
	std::string  titleTag;

public:
	std::string newEntry(std::string& filename, std::string& title, std::string& description);
	
	//builds a new title tag <title>title</title>
	std::string newTitleTag(const std::string& title);

	std::string trim(const std::string& str);
};

