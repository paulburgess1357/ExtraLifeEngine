#pragma once
#include "IShaderProgram.h"
#include "IShaderLoader.h"
#include <memory>
#include <utility>

class IShaderCompiler{
	
public:
	IShaderCompiler(const std::shared_ptr<IShaderLoader>& shader_loader)
		:m_vertex_fragment_strings{ shader_loader->load() }{
	}
	
	virtual ~IShaderCompiler() = default;
	[[nodiscard]] virtual std::shared_ptr<IShaderProgram> compile() const = 0;
	
protected:
	std::pair<std::string, std::string> m_vertex_fragment_strings;
		
};