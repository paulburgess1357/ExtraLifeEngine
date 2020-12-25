#pragma once
#include <exception>
#include <string>

namespace StringUtil {

	class LoadFileToStringException : public std::exception {

	public:
		LoadFileToStringException(const std::string& file_path) :
			m_error_string{ "Unable to load file: " + file_path } {

		}

		const char* what() const {
			return m_error_string.c_str();
		}

	private:
		std::string m_error_string;
	};

} // namespace StringUtil