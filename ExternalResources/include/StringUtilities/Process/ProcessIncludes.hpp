#pragma once
#include "../SubString/SubString.hpp"
#include "IncludesResource.hpp"
#include <string>
#include <vector>
#include <unordered_map>

namespace StringUtil {

	class ProcessIncludes {

	public:

		ProcessIncludes() = default;

		static std::string process(std::string process_string) {

			// Replaces the text: #include "file_path_to_include_file"
			// with the contents of the include file.  All includes are processed,
			// including includes within the include files.

			IncludesResource includes_resource;
			std::vector<size_t> include_locations = SubString::find_all_starting_indices(process_string, "#include");

			while (!include_locations.empty()) {

				const size_t include_start_index = include_locations.at(0);
				const std::string processed_sub_string = process_string.substr(include_start_index);

				const size_t first_index = SubString::find_index(processed_sub_string, "\"", 1);
				const size_t second_index = SubString::find_index(processed_sub_string, "\"", 2);
				const std::string include_path = SubString::find_string_btwn_indices(processed_sub_string, first_index + 1, second_index - 1);

				std::string include_string = includes_resource.load(include_path);

				process_string.erase(include_start_index, second_index + 1);
				process_string.insert(include_start_index, include_string);

				include_locations = SubString::find_all_starting_indices(process_string, "#include");
			}

			return process_string;
		}

	};
	
} // namespace StringUtil