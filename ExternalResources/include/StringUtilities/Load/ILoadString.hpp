#pragma once
#include <string>

namespace StringUtil {

	class ILoadString {

	public:
		virtual ~ILoadString() = default;
		virtual std::string load() const = 0;

	};

} // namespace StringUtil
