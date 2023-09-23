#include "Pages.h"


bool Pages::pageExists(const std::string &filename,const fs::path& path_to_directory)
{
	fs::path filepath = path_to_directory / filename;
	//std::cout << "filepath is: " << filepath << "\n";
	return fs::exists(filepath);
}

bool Pages::CreateHTMLFile(std::string fileName, fs::path& directory)
{
	std::cout << "Page " << fileName << " created in : " << directory.string() << "\n";

	if (!pageExists(fileName,directory))
	{
		std::ofstream newFile(fileName);

		if (newFile.is_open())
		{
			//writing data to new file from template.
			
			//add title tag
			
			//update wikilog index page to add newly created entry (see newEntry on HTML.h)

		}
	}
	else {
		//create modal in here or something to warn me that the file exists already
		std::cout << "Sorry a page with the same name already exists.Mind giving it another name ?\n";
	}

	return true;
}