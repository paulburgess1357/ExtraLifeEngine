#pragma once
#include <exception>
#include <string>

namespace StringUtil {

	class IndexOutsideRangeException : public std::exception {

	public:
		IndexOutsideRangeException(const size_t index, const size_t allowed_range) :
			m_error_string{ "Index outside allowed range!\nVector size: " + std::to_string(allowed_range) + " | Index: " + std::to_string(index) } {

		}

		const char* what() const {
			return m_error_string.c_str();
		}

	private:
		std::string m_error_string;
	};

} // namespace StringUtil