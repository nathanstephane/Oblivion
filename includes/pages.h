#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "html.h"

namespace fs = std::filesystem;

class Page 
{
public:
	int overall_count;
	int project_count;
	int thoughts_count;
	int wikilog_count;

	std::string titleTag; 
	std::string path;
	std::string headerTitle;

	std::string what;
	std::string why;
	std::string how;
	std::string when;
	std::string where;

public:
	bool CreateHTMLFile(std::string fileName,fs::path& directory, Html::optional &options);
	bool pageExists(const std::string &filename, const fs::path& path_to_directory);
	void searchAndReplace(fs::path& newFile, Page& mandatoryTags, Page* optionalTags = NULL);
	void addToIndex(const fs::path& directory, std::string filename, std::string pageName, std::string desc);
	//void searchAndReplace(std::fstream& newFile, HTML::optional &options);
};

