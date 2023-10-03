#include "Pages.h"


bool Pages::pageExists(const std::string &filename,const fs::path& path_to_directory)
{
	fs::path filepath = path_to_directory / filename;
	//std::cout << "filepath is: " << filepath << "\n";
	return fs::exists(filepath);
}

void Pages::searchAndReplace(fs::path& path_of_file)
{
	std::fstream newFile;
	newFile.open(path_of_file, std::fstream::out);

	std::string string_buffer;
	//if (newFile.is_open())
	//{
	//	std::cout << "\nOPENED";
	//	newFile >> string_buffer;
	//	std::cout << string_buffer;
	//}
	while (!newFile.eof())
	{
		std::getline(newFile,string_buffer);
		std::cout << string_buffer;
	}
}

bool Pages::CreateHTMLFile(std::string fileName, fs::path& directory, HTML::optional &options)
{
	//std::cout << "Page " << fileName << " created in : " << directory.string() << "\n";
	//std::cout << "Page " << fileName << " created in : " << directory.filename() << "\n";
	//if (directory.filename() == "wikilog")
	//	std::cout << "BOUYA";

	if (!pageExists(fileName,directory))
	{
		fs::path filepath = directory / fileName;
		std::cout << filepath;
		std::fstream newFile;
		newFile.open(directory / fileName, std::fstream::out);

		std::fstream templatefile;
		templatefile.open(directory/"template.obxg", std::ios::in);

		if (newFile.is_open())
		{
		
			std::string stringbuffer;
			//writing data to new file from template.
			while (!templatefile.eof())
			{
				std::cout << "DURK";
				std::getline(templatefile,stringbuffer);
				newFile << stringbuffer << std::endl;
			}
			

			searchAndReplace(filepath);
			newFile.close();
			//if (directory.filename() == "projects")
				//searchAndReplace(newFile, options);
			// title tag
			
			// path navigator tag
			
			// h2
			 
			//update wikilog index page to add newly created entry (see newEntry on HTML.h)
			
		
		}
		
		templatefile.close();
	}
	else {
		//create modal in here or something to warn me that the file exists already
		std::cout << "Sorry a page with the same name already exists.Mind giving it another name ?\n";
	}

	return true;
}