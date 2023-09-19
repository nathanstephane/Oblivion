#include "Gui.h"


void Gui::DisplayMenu()
{
	ImGui::Text("You are here: %s/", currentPath.filename().string().c_str());

	if (currentPath.stem() == "Oblivion")
	{
		//prevent me from going backward
	}

	if (ig::Button("Back"))
	{
		if (currentPath.has_parent_path()) 
		{
			nextPath = currentPath;
			currentPath = currentPath.parent_path();
		}
		
		

		//TODO: implement Next using selectable.. check if a dir has been selected then update it when back has been pressed.
	}
}

void Gui::DisplayContent()
{
	for (const auto& item : fs::directory_iterator(currentPath))
	{
		const bool is_dir = item.is_directory();
		const bool is_file = item.is_regular_file();

		std::string item_name = item.path().filename().string();

		if (is_dir)
		{
			item_name = "Dir: " + item_name;
		}
		else if (is_file)
		{
			auto filesize = std::to_string(fs::file_size(item));
			
			
			item_name = "Fle: " + item_name + " "+ filesize;
			//item_name = "Fle: " + item_name;
		}

		//ImGui::Text("%s",item_name.c_str());
		if (ImGui::Selectable(item_name.c_str()))
		{
			std::cout << "Selected path: " << item.path() << "\n";
			std::cout << "Selected name: " << item_name << "\n";
		}	
	}



}

void Gui::metrics()
{
	overall_count = 0;
	project_count = 0;
	thoughts_count = 0;
	wikilog_count = 0;
	for (const auto& item : fs::recursive_directory_iterator(path_bitofshell))
	{
		if (item.path().extension() == ".html")
		{
			++overall_count;

		}

		if (item.is_directory())
		{
			if (item.path().filename() == "projects")
				for (const auto& pr : fs::recursive_directory_iterator(item))
					if (pr.path().extension() == ".html")
						++project_count;

			if (item.path().filename() == "thoughts")
				for (const auto& th : fs::recursive_directory_iterator(item))
				{
					if (th.path().extension() == ".html")
						++thoughts_count;
				}

			if (item.path().filename() == "wikilog")
				for (const auto& wk : fs::recursive_directory_iterator(item))
				{
					if (wk.path().extension() == ".html")
						++wikilog_count;
				}


		}

	}
	/*std::cout << overall_count << " files\n";
	std::cout << project_count << " projects files\n";
	std::cout << thoughts_count << " thoughts files\n";
	std::cout << wikilog_count << " wikilog files\n";*/
}