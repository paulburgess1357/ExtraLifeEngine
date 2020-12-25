#include "ShaderLoaderFromFile.h"
#include "StringUtilities/Load/LoadFileToString.hpp"

ShaderLoaderFromFile::ShaderLoaderFromFile(const std::string& vertex_filepath, const std::string& fragment_filepath)
	:m_vertex_filepath {vertex_filepath},
	m_fragment_filepath{fragment_filepath}{	
}

std::pair<std::string, std::string> ShaderLoaderFromFile::load() const{
	const std::string vertex_shader = StringUtil::LoadFileToString::load(m_vertex_filepath);
	const std::string fragment_shader = StringUtil::LoadFileToString::load(m_fragment_filepath);
	
	const StringUtil::LoadFileToString fragment_loader{ m_fragment_filepath };
	std::pair<std::string, std::string> loaded_shaders{ vertex_shader, fragment_shader };
	return loaded_shaders;
}
