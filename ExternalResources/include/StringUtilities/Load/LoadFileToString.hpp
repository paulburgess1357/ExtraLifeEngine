#pragma once
#include "ILoadString.hpp"
#include "LoadFileToStringException.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace StringUtil {

	class LoadFileToString : public ILoadString {

	public:
		LoadFileToString(const std::string& file_path)
			:m_filepath{ file_path } {

		}

		static std::string load(const std::string& file_path) {
			const LoadFileToString string_loader{ file_path };
			return string_loader.load();
		}

	private:

		std::string load() const override {

			std::stringstream ss;
			std::ifstream file;

			try {
				file.open(m_filepath);
				if (!file.fail()) {
					ss << file.rdbuf();
				} else {
					throw LoadFileToStringException(m_filepath);
				}
				file.close();
			}
			catch (LoadFileToStringException& load_error) {
				std::cerr << load_error.what() << std::endl;
				exit(1);
			}
			return ss.str();
		}

		std::string m_filepath;

	};

} // namespace StringUtil