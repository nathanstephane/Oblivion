#include "../includes/pages.h"


bool Page::pageExists(const std::string &filename,const fs::path& path_to_directory)
{
	return fs::exists(path_to_directory / filename);
}

void Page::searchAndReplace(fs::path& path_of_file, Page& mandatoryTags, Page* optionalTags)
{

	std::ifstream fin(path_of_file);
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

	std::string whatToken  = "<!--token::what_ <p><u>What</u>:</p> -->";
	std::string whyToken   = "<!--token::why_ <p><u>Why</u>:</p> -->";
	std::string howToken   = "<!--token::how_ <p><u>How</u>:</p> -->";
	std::string whenToken  = "<!--token::when_ <p><u>When</u>:</p> -->";
	std::string whereToken = "<!--token::where_ <p><u>Where</u>:</p> -->";

	//replaceToken, value
	std::unordered_map<std::string, std::string> keyToRepl =
	{
		{searchTitleTag,mandatoryTags.titleTag},
		{searchPath,mandatoryTags.path},
		{searchHeaderTitle, mandatoryTags.headerTitle}
	};

	if (optionalTags != NULL)
	{
		if (!optionalTags->what.empty()) keyToRepl[whatToken] = optionalTags->what;
		if (!optionalTags->why.empty()) keyToRepl[whyToken] = optionalTags->why;
		if (!optionalTags->how.empty()) keyToRepl[howToken] = optionalTags->how;
		if (!optionalTags->when.empty()) keyToRepl[whenToken] = optionalTags->when;
		if (!optionalTags->where.empty()) keyToRepl[whereToken] = optionalTags->where;
	}
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
	if (optionalTags != NULL) optionalTags = NULL;
	
}

bool Page::CreateHTMLFile(std::string fileName, fs::path& directory, Html::optional &options)
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
		std::cerr << "Sorry a page with the same name already exists.Mind giving it another name ?\n";
		return 0;
	}
}

void Page::addToIndex(const fs::path& directory, std::string filename, std::string pageName, std::string desc)
{
	std::cout << "\nNOTHING";
	std::cout << "\n directory: " << directory << "\n";
	std::cout << "SKfilename: " << filename << "\n";
	//std::cout << "description: " << desc<< "\n";
	
	std::string file = directory.string() + "\\index.html";
	std::cout << "FILE TO OPEN: " << file << "\n";
	std::ifstream fin(file);
	
		if (!fin){
			std::cerr << "Error opening file" << std::endl;
		}
		else { std::cout << "Yes opened\n"; }

	std::string text((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	fin.close();

	std::string searchTitleTag = "<!-- obxg:insert_new_item -->";
	std::string valueString = Html::newEntry(filename, pageName, desc)+"\n\t\t\t\t\t\t"+searchTitleTag;
	std::cout << valueString << "\n";
	
		size_t pos = 0;
		while ((pos = text.find(searchTitleTag, pos)) != std::string::npos)
		{
			std::cout << "Yes replaced\n";
			text.replace(pos, searchTitleTag.length(), valueString);
			pos += valueString.length();
		}
	
	std::ofstream fout(file, std::ios::trunc);
	if (!fout)
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}
	fout << text;
	fout.close();
}


