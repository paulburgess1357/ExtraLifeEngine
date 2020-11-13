#pragma once
#include "../../Interfaces/Shader/IShaderLoader.h"
#include <string>
#include <utility>

class ShaderLoaderFromFile : public IShaderLoader{
	
public:
	ShaderLoaderFromFile(const std::string& shader_name, const std::string& vertex_filepath, const std::string& fragment_filepath);
	std::pair<std::string, std::string> load() const override;
	
private:
	std::string m_vertex_filepath;
	std::string m_fragment_filepath;
	
};

