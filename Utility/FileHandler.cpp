#include "FileHandler.h"
#include <filesystem>

std::vector<std::string> FileHandler::list_directory_filenames(const std::string& directory_path){
	std::vector<std::string> file_names;
	for(const auto& file : std::filesystem::directory_iterator(directory_path)){
		file_names.push_back(file.path().filename().u8string());
	}
	return file_names;	
}
