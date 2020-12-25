#pragma once
#include <string>

namespace StringUtil{

	class FilePath {

	public:
		static std::string get_filename(const std::string& filepath) {
			return filepath.substr(filepath.find_last_of("/\\") + 1);
		}

		static std::string get_extension(const std::string& filename) {
			return filename.substr(filename.find_last_of('.') + 1);
		}

		static std::string get_directory(const std::string& filepath) {
			return filepath.substr(0, filepath.find_last_of("/\\")) + "/";
		}

	};
	
} // namespace StringUtil

