#include "HTML.h"


std::string HTML::newEntry(std::string& filename, std::string& title, std::string& description)
{
	std::string formatedOutput;

	formatedOutput = "<a href=\""+ filename + "\">				\
						<li class = \"bgHover\"><u>"+title+"</u> \
					</a>";
}