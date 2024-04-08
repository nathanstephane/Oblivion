#include "../includes/gui.h"


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
		
			ImGui::OpenPopup("CREATE HTML FILE");
				
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
}

void Gui::createFilePopup(fs::path& selectedDir)
{
	//std::cout << selectedDir << "\n";
	if (ImGui::BeginPopupModal("CREATE HTML FILE", &open_createModal) )
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
			
		//mandatory
		Html maker;
		mandatoryData.titleTag = maker.maketitleTag(title);
		mandatoryData.path = maker.navPath(selectedDir, title);
		mandatoryData.headerTitle = maker.makeheaderTag(title);
		
		std::string description;
	
		ImGui::PushID(1);
		ImGui::Text("Desc:");
		ImGui::SameLine();
		static char desc[1000] = { '\0' };
		ImGui::InputText("####", desc, sizeof(desc));
		description = desc;
		ImGui::PopID();

		if (selectedDir.filename() == "projects")
		{
				ImGui::SameLine();
				ImGui::Checkbox("Use desc as What ?", &desc_is_what);
				if (desc_is_what)
				{
					optns.what = true;
					optionalData.what = maker.optionalTag("What:" + description);
				}

				ImGui::Checkbox("What ?", &optns.what);
				optns.what ? optionalData.what = maker.optionalTag("What") : optionalData.what = "";

				ImGui::Checkbox("Why ?", &optns.why);
				optns.why ? optionalData.why = maker.optionalTag("Why") : optionalData.why = "";

				ImGui::Checkbox("How ?", &optns.how);
				optns.how ? optionalData.how = maker.optionalTag("How") : optionalData.how = "";
				
				ImGui::Checkbox("When ?", &optns._when);
				optns._when ?optionalData.when = maker.optionalTag("When") : optionalData.when = "";
			
				ImGui::Checkbox("Where ?", &optns.where);
				optns.where ? optionalData.where = maker.optionalTag("Where") : optionalData.where = "";
		}

	if (ImGui::Button("Create Page"))
		{
			std::string wholeFile = pagename + extension;
			
			if (CreateHTMLFile(wholeFile, selectedDir, optns))
			{
				fs::path filepath = selectedDir / wholeFile;
				if (selectedDir.filename() == "projects")
				{
					searchAndReplace(filepath,mandatoryData,&optionalData);

					addToIndex(selectedDir,wholeFile,pagename,description);
				}
				else {
					searchAndReplace(filepath, mandatoryData);
				}
			}
		}
		ImGui::EndPopup();
	}	
}
