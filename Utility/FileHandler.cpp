#include "FileHandler.h"
#include "FatalError.h"

std::string FileHandler::get_file_directory(const std::string& filepath){

    size_t pos = filepath.find_last_of("\\/");

	if(pos == std::string::npos){
		FatalError::fatal_error("Unable to get the directory from path: " + filepath);
	}
	
	return filepath.substr(0, pos);
	
}