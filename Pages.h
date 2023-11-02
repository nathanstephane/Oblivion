#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "HTML.h"

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
	bool CreateHTMLFile(std::string fileName,fs::path& directory, HTML::optional &options);
	bool pageExists(const std::string &filename, const fs::path& path_to_directory);
	void searchAndReplace(fs::path& newFile);
	//void searchAndReplace(std::fstream& newFile, HTML::optional &options);
};

