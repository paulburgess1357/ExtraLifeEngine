#pragma once
#include <string>
#include <vector>

class FileHandler{

public:
	static std::vector<std::string> list_directory_filenames(const std::string& directory_path);	
};

