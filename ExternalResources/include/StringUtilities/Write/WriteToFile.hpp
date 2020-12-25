#pragma once
#include <string>
#include <fstream>
#include <iostream>

namespace StringUtil{

	class WriteToFile {

	public:
		static void write(const std::string& string, const std::string& filepath) {
			std::cout << "Writing to: " + filepath << std::endl;
			std::ofstream out(filepath);
			out << string;
		}
	};
	
} // namespace StringUtil