#pragma once
#include "../Load/LoadFileToString.hpp"
#include "IncludeNotLoadedException.hpp"
#include <string>
#include <unordered_map>

namespace StringUtil{

	class IncludesResource {

		// Loads and stores include path data

	public:
		IncludesResource() = default;

		std::string load(const std::string& include_path) {
			if (!is_loaded(include_path)) {
				std::cout << "Loading: " + include_path << std::endl;
				const std::shared_ptr<ILoadString> string_loader = std::make_shared<LoadFileToString>(include_path);

				m_includes_cache[include_path] = string_loader->load();
			}

			return get(include_path);
		}

		std::string get(const std::string& include_path) {

			try {
				if (!is_loaded(include_path)) {
					throw IncludeNotLoadedException(include_path);
				}
				return m_includes_cache.at(include_path);
			}

			catch (IncludeNotLoadedException& load_error) {
				std::cerr << load_error.what() << std::endl;
				exit(1);
			}
		}


	private:

		bool is_loaded(const std::string& include_path) {
			const auto it = m_includes_cache.find(include_path);
			if (it == m_includes_cache.end()) {
				return false;
			}
			return true;
		}

		// <include path, include data>
		std::unordered_map<std::string, std::string> m_includes_cache;

	};
	
} // namespace StringUtil