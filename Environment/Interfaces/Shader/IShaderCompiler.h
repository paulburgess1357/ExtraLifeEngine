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
	[[nodiscard]] virtual std::unique_ptr<IShaderProgram> compile(const bool set_default_lights) const = 0;
	[[nodiscard]] static std::shared_ptr<IShaderCompiler> create_compiler(const std::shared_ptr<IShaderLoader>& shader_loader);
	
protected:
	std::pair<std::string, std::string> m_vertex_fragment_strings;
		
};