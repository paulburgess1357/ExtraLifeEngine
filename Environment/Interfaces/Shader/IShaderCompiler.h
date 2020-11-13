#pragma once
#include "IShaderProgram.h"
#include <memory>
#include <string>
#include <utility>

class IShaderCompiler{
	
public:
	IShaderCompiler(const std::shared_ptr<IShaderLoader>& shader_loader, std::pair<std::string, std::string> vertex_fragment_strings)
		:m_shader_loader { shader_loader },
		m_vertex_fragment_strings {vertex_fragment_strings}{		
	}
	
	virtual ~IShaderCompiler() = default;
	virtual std::shared_ptr<IShaderProgram> compile() const = 0;
	
protected:
	std::shared_ptr<IShaderLoader> m_shader_loader;
	std::pair<std::string, std::string> m_vertex_fragment_strings;
	
};