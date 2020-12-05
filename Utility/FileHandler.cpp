#include "FileHandler.h"
#include "FatalError.h"
#include <filesystem>

std::string FileHandler::get_file_directory(const std::string& filepath){

    size_t pos = filepath.find_last_of("\\/");

	if(pos == std::string::npos){
		FatalError::fatal_error("Unable to get the directory from path: " + filepath);
	}
	
	return filepath.substr(0, pos);
	
}

std::vector<std::string> FileHandler::list_directory_filenames(const std::string& directory_path){

	std::vector<std::string> file_names;
	for(const auto& file : std::filesystem::directory_iterator(directory_path)){
		file_names.push_back(file.path().filename().u8string());
	}

	return file_names;
	
}

std::string FileHandler::get_filename_extension(const std::string& filename){
	return filename.substr(filename.find(".") + 1);
}

