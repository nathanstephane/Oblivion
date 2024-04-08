#pragma warning(disable : 4996 )
#include "html.h"

 std::string Html::trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	size_t last = str.find_last_not_of(" \t\n\r");

	if (first == std::string::npos || last == std::string::npos)
	{
		return "";
	}
	return str.substr(first, last - first + 1);
}

 std::string tab(int n)
{
	 char t = '\t';
	 std::string tabs = "";
	 while (n>0)
	 {
		 tabs += t;
		 n--;
	 }
	 return tabs;
}

std::string Html::navPath(const fs::path& dir, std::string title)
{
	//std::string navigation_path;

return "<nav>You are here://<a href=\"../index.html\">obxigus</a>/\
<a href=\"../"+dir.filename().string()+"/index.html\">"+dir.filename().string()+"</a>/"+trim(title)+"\
<span class=\"blink\">|</span></nav>";
	
	//return navigation_path;
}

std::string Html::generated()
{
	time_t time_now = time(0);
	char* date = ctime(&time_now);
	std::string strDate = date;

	return "<!-- Generated with Oblivion on "+strDate+" -->";
}

//in index of category pages
 std::string Html::newEntry(std::string& filename, std::string& title, std::string& description)
{
	std::string formatedOutput;

	formatedOutput = "\n"+tab(6)+"<div class=\"item\">\n"
		+tab(7)+"<a href=\"" + filename + "\">\n"
		+tab(8)+"<li><u>" + trim(title) + "</u></li>\n"
		+tab(7)+"</a>\n";
	if (!description.empty())
		formatedOutput += tab(7)+"<p>" + description + "</p>\n";
	formatedOutput+= tab(6)+"</div> ";
	
	return formatedOutput;
}

//"<title>"title"</title>"
std::string Html::maketitleTag(const std::string& title)
{
	return "<title>"+ trim(title) + "</title>";
}

//<h2>title</h2>
std::string Html::makeheaderTag(const std::string& title)
{
	return "<h2>" + trim(title) + "</h2>";
}

std::string Html::optionalTag(const std::string& kind)
{
	return "<p><u>"+ trim(kind) + "<u>:</p>";
}