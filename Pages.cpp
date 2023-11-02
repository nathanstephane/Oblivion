#include "Pages.h"


bool Pages::pageExists(const std::string &filename,const fs::path& path_to_directory)
{
	fs::path filepath = path_to_directory / filename;
	//std::cout << "filepath is: " << filepath << "\n";
	return fs::exists(filepath);
}

void Pages::searchAndReplace(fs::path& path_of_file)
{
	std::cout << path_of_file << "\n";
	// Open the file for reading
	std::ifstream fin(path_of_file);
	// Check if the file was opened successfully
	if (!fin)
	{
		std::cerr << "Error opening file" << std::endl;
		
	}
	// Read the contents of the file into a string
	std::string text(
		(std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>());
	fin.close();
	// Perform the search and replace operation on the string
	std::string search = "<!-- obxg:<title></title> -->";
	std::string replace = "Pistache";
	size_t pos = 0;
	while ((pos = text.find(search, pos)) != std::string::npos)
	{
		text.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	// Open the file for writing
	std::ofstream fout(path_of_file, std::ios::trunc);
	// Check if the file was opened successfully
	if (!fout)
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}
	// Write the modified string back to the file
	fout << text;
	fout.close();
}

bool Pages::CreateHTMLFile(std::string fileName, fs::path& directory, HTML::optional &options)
{
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
