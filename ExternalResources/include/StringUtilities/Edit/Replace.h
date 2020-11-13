#pragma once
#include <string>

namespace StringUtil{

	namespace Edit {

		namespace Replace {

			// Simple string replacement functions
			
			std::string replace_string(std::string parse_string,
				const std::string& replacement_search,
				const std::string& replacement_string
			);

			std::string replace_entire_line(const std::string& parse_string,
				const size_t edit_line_num,
				const std::string& replacement_string
			);

		} // namespace Replace

	} // namespace Edit
		
} // namespace StringUtil
