#pragma once
#include <string>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;

class HTML
{
public:
	struct optional
	{
		bool what = false;
		bool why = false;
		bool how = false;
		bool when = false;
		bool where = false;
	};
private:
	std::string  titleTag;

public:
	std::string newEntry(std::string& filename, std::string& title, std::string& description);
	
	//builds a new title tag <title>title</title>
	std::string maketitleTag(const std::string& title);

	//builds a new header tag <h2>title</h2>
	std::string makeheaderTag(const std::string& title);

	//removes unnecessary leading whitespaces
	std::string trim(const std::string& str);

	// builds a new navigation path at  <!-- obxg:<nav>path</nav> -->
	std::string navPath(const fs::path& dir,std::string title);

	std::string generated();

};

