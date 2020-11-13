#pragma once
#include <vector>
#include <string>

namespace StringUtil {

	namespace Find {

		class IStringFinder {

		public:
			virtual ~IStringFinder() = default;
			virtual std::vector<std::string> get_strings_between(
				const std::string& parse_string, const std::string& val1, 
				const std::string& val2) const = 0;
		};

	} // namespace Find
		
} // namespace StringUtil