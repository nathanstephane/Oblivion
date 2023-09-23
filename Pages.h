#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

class Pages
{
protected:
	int overall_count;
	int project_count;
	int thoughts_count;
	int wikilog_count;

	std::string title; 

public:
	bool CreateHTMLFile(std::string fileName,fs::path& directory);
	bool pageExists(const std::string &filename, const fs::path& path_to_directory);
};

