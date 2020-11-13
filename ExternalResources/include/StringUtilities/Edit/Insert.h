#pragma once
#include <string>

namespace StringUtil{

	namespace Edit {		
		
		namespace Insert{

			// Inserts strings above, below, front, or back
			
			std::string insert_above(const std::string& parse_string, const std::string& concat_string, const size_t edit_line_num);
			std::string insert_below(const std::string& parse_string, const std::string& concat_string, const size_t edit_line_num);
			std::string insert_front(const std::string& parse_string, const std::string& concat_string, const size_t edit_line_num);
			std::string insert_back(const std::string& parse_string, const std::string& concat_string, const size_t edit_line_num);

			std::string insert_above(const std::string& parse_string, const std::string& concat_string);
			std::string insert_below(const std::string& parse_string, const std::string& concat_string);
			std::string insert_front(const std::string& parse_string, const std::string& concat_string);
			std::string insert_back(const std::string& parse_string, const std::string& concat_string);
			
		} // namespace Insert
			
	} // namespace Edit

} // namespace StringEdit