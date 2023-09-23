#include "HTML.h"

std::string HTML::trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	size_t last = str.find_last_not_of(" \t\n\r");

	if (first == std::string::npos || last == std::string::npos)
	{
		return "";
	}
	return str.substr(first, last - first + 1);
}



std::string HTML::newEntry(std::string& filename, std::string& title, std::string& description)
{
	std::string formatedOutput;

	formatedOutput = "<a href=\""+ filename + "\">\n				\
						\t<li class = \"bgHover\"><u>"+ trim(title)+"</u>\n";
					if (!description.empty())
						formatedOutput += "\t<br><span><em>"+description+"</em></span>\n";
	formatedOutput += "</li>\n</a>";
					//</a>";
	return formatedOutput;
}

std::string HTML::newTitleTag(const std::string& title)
{
	return "<title>"+ trim(title) + "</title>";
}


