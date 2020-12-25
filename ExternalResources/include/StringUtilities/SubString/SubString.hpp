#pragma once
#include "IndexOutsideRangeException.hpp"
#include <string>
#include <vector>
#include <iostream>

namespace StringUtil {

	class SubString {

	public:
		static std::vector<size_t> find_all_starting_indices(const std::string& search_string, const std::string& find_string) {

			// Returns a vector of all the starting indices of the substring

			std::vector<size_t> string_positions;
			size_t position = search_string.find(find_string);

			while (position != std::string::npos) {
				string_positions.push_back(position);
				position = search_string.find(find_string, position + 1);
			}

			return string_positions;
		}

		static size_t find_index(const std::string& search_string, const std::string& find_string, const size_t occurance) {

			// Returns the 1st/2nd/3rd/etc index as defined by the user

			try {
				std::vector<size_t> all_indices = find_all_starting_indices(search_string, find_string);
				const size_t vector_index = occurance - 1;

				if (vector_index + 1 > all_indices.size()) {
					std::cout << "Search Value: " + find_string << std::endl;
					throw IndexOutsideRangeException(vector_index + 1, all_indices.size());
				}

				return all_indices.at(vector_index);
			}

			catch (IndexOutsideRangeException& range_error) {
				std::cerr << range_error.what() << std::endl;
				exit(1);
			}

		}

		static std::string find_string_btwn_indices(const std::string& search_string, const size_t start_index, const size_t end_index) {

			// Return the substring value between two indices.  Start and end index
			// are inclusive

			// Start and end index are inclusive
			return std::string(search_string.begin() + start_index, search_string.begin() + end_index + 1);
		}

	};

} // namespace StringUtil