#pragma once
#include "IStringFinder.h"

namespace StringUtil {

	namespace Find {

		class SingleLine : public StringUtil::Find::IStringFinder {

		public:
			SingleLine() = default;
			std::vector<std::string> get_strings_between(
				const std::string& parse_string, 
				const std::string& val1, 
				const std::string& val2) const override;
		};

	} // namespace Find

} // namespace StringUtil