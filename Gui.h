#pragma once
#include <filesystem>
#include <iostream>
#include "imgui.h"
#include "Pages.h"

namespace fs = std::filesystem; namespace ig = ImGui;

class Gui : Pages
{
private:
	fs::path currentPath;
	fs::path nextPath;

	fs::path path_bitofshell;

public:
	Gui() :currentPath(fs::current_path()){
		if (fs::exists(fs::current_path()/="bitofshell"))
		{
			std::cout << "Path exist";
			path_bitofshell = fs::current_path() /= "bitofshell";
		}
	}
public:
	void DisplayMenu();
	void DisplayContent();
	void metrics();

	int get_overallcount()
	{
		return overall_count;
	}
	int get_projectsCount()
	{
		return project_count;
	}
	int get_thoughtsCount()
	{
		return thoughts_count;
	}
	int get_wikilogCount()
	{
		return wikilog_count;
	}


};

