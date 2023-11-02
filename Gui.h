#pragma once
#include <filesystem>
#include <iostream>
#include "imgui.h"
#include "Pages.h"
#include <stack>
#include <cstring>

namespace fs = std::filesystem; namespace ig = ImGui;

class Gui : Pages
{
private:
	fs::path currentPath;
	fs::path nextPath;
	fs::path selected_item;
	fs::path last_visited;

	fs::path path_bitofshell;
	std::stack<fs::path> history;

	fs::path project_dir;
	fs::path thoughts_dir;
	fs::path wikilog_dir ;
	fs::path dirPages;

	bool open_createModal=false;
	bool pagename_is_title = false;

	HTML::optional optns;
public:
	Gui() : currentPath(fs::current_path()){
		selected_item = fs::path{};
		if (fs::exists(fs::current_path()/="bitofshell"))
		{
			std::cout << "Path exists.\n";
			path_bitofshell = fs::current_path() /= "bitofshell";

			 project_dir = fs::current_path() /= "bitofshell\\projects";
			 thoughts_dir = fs::current_path() /= "bitofshell\\thoughts";
			 wikilog_dir = fs::current_path() /= "bitofshell\\wikilog";
		}
		
		
	}
public:
	void DisplayMenu();
	void DisplayContent();
	void DisplayActions();
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

	void createFilePopup(fs::path& selectedDir);
};

