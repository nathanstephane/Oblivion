#pragma once
#include <string>
#include <filesystem>
#include <ctime>

#include <iostream>
namespace fs = std::filesystem;

class Html
{
public:
	struct optional
	{
		bool what = false;
		bool why = false;
		bool how = false;
		
		bool where = false;
		bool _when = false;
	};

	struct mandatory
	{
		std::string header_title(const std::string& title) { return "<title>"+title+"</title>"; };
		std::string navigation_path(const std::string& title, const std::string& where)
		{
			//hardcoding for now. Will need to change this later 
		}
		std::string body_title;
	};
private:
	std::string  titleTag;

public:
	static std::string newEntry(std::string& filename, std::string& title, std::string& description);
	
	//builds a new title tag <title>title</title>
	std::string maketitleTag(const std::string& title);

	//builds a new header tag <h2>title</h2>
	std::string makeheaderTag(const std::string& title);

	//removes unnecessary leading whitespaces
	static std::string trim(const std::string& str);

	// builds a new navigation path at  <!-- obxg:<nav>path</nav> -->
	std::string navPath(const fs::path& dir,std::string title);

	std::string optionalTag(const std::string& kind);

	std::string generated();

};

