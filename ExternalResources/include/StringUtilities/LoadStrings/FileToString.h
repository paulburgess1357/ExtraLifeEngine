#pragma once
#include "ILoadString.h"
#include <string>

namespace StringUtil {

	namespace Load {

		class FileToString : public StringUtil::Load::ILoadString {

		public:
			FileToString(const std::string& filepath);
			~FileToString() = default;
			std::string load_string() const override;
		private:
			std::string m_filepath;
		};

	} // namespace Load

} // namespace StringUtil
