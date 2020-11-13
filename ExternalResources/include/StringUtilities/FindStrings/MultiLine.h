#pragma once
#include "IStringFinder.h"
#include <vector>
#include <string>

namespace StringUtil{

	namespace Find {

		class MultiLine : public StringUtil::Find::IStringFinder {

			// Locates string values and/or lines based on a start string
			// and end string
			
		public:
			std::vector<std::string> get_strings_between(
				const std::string& parse_string, 
				const std::string& val1, 
				const std::string& val2) const override;
			std::vector<size_t> get_line_numbers(
				const std::string& parse_string, 
				const std::string& match_value) const;
		};
		
	} // namespace Find
		
} // namespace StringUtil



