#pragma once
#include <exception>
#include <string>

namespace StringUtil{

	class IncludeNotLoadedException : public std::exception {

	public:
		IncludeNotLoadedException(const std::string& include_path) :
			m_error_string{ "Include file not loaded: " + include_path } {

		}

		const char* what() const {
			return m_error_string.c_str();
		}

	private:
		std::string m_error_string;
	};
	
} // namespace StringUtil


