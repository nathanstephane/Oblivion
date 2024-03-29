#pragma warning(disable : 4996 )
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

std::string HTML::navPath(const fs::path& dir, std::string title)
{
	std::string navigation_path;

navigation_path = "<nav>You are here://<a href=\"../index.html\">obxigus</a>/\
<a href=\"../"+dir.filename().string()+"/index.html\">"+dir.filename().string()+"</a>/"+trim(title)+"\
<span class=\"blink\">|</span></nav>";
	
	return navigation_path;
}

std::string HTML::generated()
{
	time_t time_now = time(0);
	char* date = ctime(&time_now);
	std::string strDate = date;

	return "<!-- Generated with Oblivion on "+strDate+" -->";
}

//in index of category pages
 std::string HTML::newEntry(std::string& filename, std::string& title, std::string& description)
{
	std::string formatedOutput;

	/*formatedOutput = "<a href=\""+ filename + "\">\n\
\t<li class = \"bgHover\"><u>"+	trim(title)+"</u>\n";
					if (!description.empty())
						formatedOutput += "\t<br><span><em>"+description+"</em></span>\n";
	formatedOutput += "</li>\n</a>";*/

	formatedOutput = " <div class=\"item\">\n"
		"\t<a href=\"" + filename + ":\">\n"
		"\t\t<li><u>" + trim(title) + "</u></li>\n"
		"\t</a>\n";
	if (!description.empty())
		formatedOutput += "\t<p>" + description + "</p>\n";
	formatedOutput+="</div> ";
	
	return formatedOutput;
}

//"<title>"title"</title>"
std::string HTML::maketitleTag(const std::string& title)
{
	return "<title>"+ trim(title) + "</title>";
}

//<h2>title</h2>
std::string HTML::makeheaderTag(const std::string& title)
{
	return "<h2>" + trim(title) + "</h2>";
}

std::string HTML::optionalTag(const std::string& kind)
{
	return "<p><u>"+ trim(kind) + "<u>:</p>";
}