#pragma once
#include <string>

namespace StringUtil {

	namespace Load {

		class ILoadString {

		public:
			virtual ~ILoadString() = default;
			virtual std::string load_string() const = 0;
		};

	} // namespace Load

} // namespace StringUtil