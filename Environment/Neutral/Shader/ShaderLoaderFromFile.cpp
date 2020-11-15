#include "ShaderLoaderFromFile.h"
#include "StringUtilities/LoadStrings/FileToString.h"

ShaderLoaderFromFile::ShaderLoaderFromFile(const std::string& vertex_filepath, const std::string& fragment_filepath)
	:m_vertex_filepath {vertex_filepath},
	m_fragment_filepath{fragment_filepath}{	
}

std::pair<std::string, std::string> ShaderLoaderFromFile::load() const{
	const StringUtil::Load::FileToString vertex_file_loader{ m_vertex_filepath };
	const StringUtil::Load::FileToString fragment_loader{ m_fragment_filepath };
	std::pair<std::string, std::string> loaded_shaders{ vertex_file_loader.load_string(), fragment_loader.load_string() };	
	return loaded_shaders;
}
