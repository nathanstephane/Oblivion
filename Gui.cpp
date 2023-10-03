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
			//nextPath = currentPath;
			last_visited = currentPath;
			currentPath = currentPath.parent_path();
			
			
			if(!history.empty()) 
				history.pop();
			history.push(last_visited);

		}
		//std::cout << history.top();

		//TODO: implement Next using selectable.. check if a dir has been selected then update it when back has been pressed.
	}

	if (!history.empty() && history.top() != currentPath)
	{
		ImGui::SameLine();
		if (ImGui::Button("Next"))
		{
			//const auto dir = history.top();
			currentPath = history.top();
			std::cout << history.top();
		}
	}
}

void Gui::DisplayContent()
{
	for (const auto& item : fs::directory_iterator(currentPath))
	{
		const auto is_selected = item.path() == selected_item;
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
			
		}
		//ImGui::Text("%s",item_name.c_str());
		if (ImGui::Selectable(item_name.c_str(), is_selected))
		{
			if (is_dir)
			{
				history.push(item.path());
				currentPath /= item.path().filename();
				
			}
			selected_item = item.path();
		
		}	
	}



}

void Gui::DisplayActions()
{
	if (fs::is_directory(selected_item))
	{
		ImGui::Text("selected dir: %s/", selected_item.filename().string().c_str());
	}
	else if (fs::is_regular_file(selected_item))
	{
		ImGui::Text("selected file: %s", selected_item.filename().string().c_str());

	}
	else
	{
		ImGui::Text("nothing selected.");

	}

	//CREATE

	
	//check if in right directory.
	if (currentPath == project_dir ||
		currentPath == thoughts_dir ||
		currentPath == wikilog_dir)
	{
	
		if (ImGui::Button("Create"))
		{
			//Modal to prompt for file name
			dirPages = currentPath;
			open_createModal = true;
			if (currentPath==wikilog_dir)
			ImGui::OpenPopup("CREATE WIKILOG FILE");

			//Create file based on template file
				//if in wikilog/ -> ask for pagename, title
				//if in project/ -> ask for pagename, title, what?, why?, when?, where?, how?
				//if in thoughts/ -> ask for pagename, title, tag(philocyber, universe,srandom)
				
		}


	}


	//OPEN (in both vscode and browser)

	//RENAME

	//DELETE
	createFilePopup(dirPages);

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

void Gui::createFilePopup(fs::path& selectedDir)
{
	//std::cout << selectedDir << "\n";
	if (ImGui::BeginPopupModal("CREATE WIKILOG FILE", &open_createModal) )
	{
		std::string extension = ".html";
		static char pagename[300] = { '\0' };
		ImGui::Text("Page name");
		ImGui::SameLine();
		ImGui::InputText(".html", pagename, sizeof(pagename));


		ImGui::Checkbox("Use page name as title", &pagename_is_title);
		static char title[300] = { '\0' };
		if (!pagename_is_title)
		{
			ImGui::Text("Page title");
			ImGui::SameLine();
			ImGui::InputText("###", title, sizeof(title));
			
		}
		else 
		{
			std::memcpy(title,pagename,strlen(pagename)+1);
		}
		

		if (ImGui::Button("Create Page"))
		{
			HTML::optional optns;
			optns.how = false;

			std::string wholeFile = pagename + extension;
			//std::cout << "Created pagename " << wholeFile << " in " << selectedDir<<" title: "<<title <<"\n";
			CreateHTMLFile(wholeFile, selectedDir,optns);
		}
		ImGui::EndPopup();
	}
	
#pragma region comment
	//if (ImGui::BeginPopupModal("Create File"), &open_createModal)
	//{
	//	std::string extension = ".html";
	//	static char name[300] = { '\0' };
	//	ImGui::Text("Page Name: ");
	//	ImGui::InputText(".html", name, sizeof(name));
	//	
	//

	//	if (ImGui::Button("Create Html"))
	//	{
	//		std::string wholeFile = name + extension;
	//		/*if (CreateHTMLFile(wholeFile,selectedDir))
	//		{
	//			open_createModal = false;
	//			std::memset(name, 0, sizeof(name));
	//		}*/
	//	}
	//	ImGui::SameLine();
	//	if (ImGui::Button("Cancel"))
	//	{
	//		open_createModal = false;
	//	}

	//	ImGui::EndPopup();
	//}
#pragma endregion


	
}
