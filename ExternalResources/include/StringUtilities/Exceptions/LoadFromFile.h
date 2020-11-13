#pragma once
#include <exception>
#include <string>

namespace StringUtil{

	namespace Exceptions{

		class LoadFromFile : public std::exception {			

		public:
			const char* what() const override;
			LoadFromFile(const std::string& file_path);

		private:
			std::string m_error_string;
		};
				
	} // namespace Exceptions

} // namespace StringUtil



