#include "Pages.h"


bool Page::pageExists(const std::string &filename,const fs::path& path_to_directory)
{
	fs::path filepath = path_to_directory / filename;
	//std::cout << "filepath is: " << filepath << "\n";
	return fs::exists(filepath);
}

void Page::searchAndReplace(fs::path& path_of_file, Page& mandatoryTags, Page* optionalTags = NULL)
{
	std::cout << path_of_file << "\n";
	std::cout << "PAGE OBJ TITLE:"<< mandatoryTags.titleTag << "\n";
	std::cout << "PAGE OBJ PATH: " << mandatoryTags.path << "\n";
	std::cout << "PAGE OBJ PATH: " << mandatoryTags.path << "\n";
	// Opening the file for reading
	std::ifstream fin(path_of_file);
	// Checking if the file was opened successfully
	if (!fin)
	{
		std::cerr << "Error opening file" << std::endl;
	}
	// Reading the contents of the file into a string
	std::string text( (std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	fin.close();
	// Performing the search and replace operation on the string
	std::string searchTitleTag = "<!-- obxg:<title></title> -->";
	std::string searchPath = "<!-- obxg:<nav>path</nav> -->";
	std::string searchHeaderTitle = "<!-- obxg:<h2>title</h2> -->";
	std::string replaceTitle = "Pistache";

	std::string whatToken = "<!--token::what_ <p><u>What</u>:</p> -->";
	std::string whyToken = "<!--token::what_ <p><u>What</u>:</p> -->";

//	std::vector<std::string> stuffToSearch{searchTitleTag,searchPath,searchHeaderTitle,replaceTitle};
	//size_t pos = 0;

	//replaceToken, value
	std::unordered_map<std::string, std::string> keyToRepl =
	{
		{searchTitleTag,mandatoryTags.titleTag},
		{searchPath,mandatoryTags.path},
		{searchHeaderTitle, mandatoryTags.headerTitle}
	};
	for (const auto& tag : keyToRepl) 
	{
		size_t pos = 0;
		while ((pos = text.find(tag.first, pos)) != std::string::npos)
		{
			text.replace(pos, tag.first.length(), tag.second);
			pos += tag.second.length();
		}

	}

	// Opening the file for writing
	std::ofstream fout(path_of_file, std::ios::trunc);
	// Checking if the file was opened successfully
	if (!fout)
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}
	// Writing the modified string back to the file
	fout << text;
	fout.close();
}

bool Page::CreateHTMLFile(std::string fileName, fs::path& directory, HTML::optional &options)
{
	if (!pageExists(fileName,directory))
	{
		fs::path filepath = directory / fileName;
		std::cout << filepath;
		std::fstream newFile;
		newFile.open(directory / fileName, std::fstream::out);

		std::fstream templatefile;
		if (pageExists("template.obxg", directory)) {
			templatefile.open(directory / "template.obxg", std::ios::in);
		}
		else {
			std::cerr << "Template file not found" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (newFile.is_open())
		{	
			std::string stringbuffer;
			//writing data to new file from template.
			while (!templatefile.eof())
			{
				
				std::getline(templatefile,stringbuffer);
				newFile << stringbuffer << std::endl;
			}
			newFile.close();		
		}	
		templatefile.close();
		return true;
	}
	else {
		//create modal in here or something to warn me that the file exists already
		std::cout << "Sorry a page with the same name already exists.Mind giving it another name ?\n";
		return 0;
	}
}

//if (directory.filename() == "projects")
	//searchAndReplace(newFile, options);
// title tag

// path navigator tag

// h2

//update wikilog index page to add newly created entry (see newEntry on HTML.h)
