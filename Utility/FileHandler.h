#pragma once
#include <string>
#include <vector>

class FileHandler{

public:
	static std::string get_file_directory(const std::string& file_path);
	static std::vector<std::string> list_directory_filenames(const std::string& directory_path);
	static std::string get_filename_extension(const std::string& filename);
	
};

