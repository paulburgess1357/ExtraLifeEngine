#include "IShaderCompiler.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/OpenGL/Shader/OpenGLShaderCompiler.h"

std::shared_ptr<IShaderCompiler> IShaderCompiler::create_compiler(const std::shared_ptr<IShaderLoader>& shader_loader){

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLShaderCompiler>(shader_loader);
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<IShaderCompiler> shader_compiler = nullptr;
		FatalError::fatal_error("Vulkan shader compiler does not exist!.");
		return shader_compiler;
	}

	FatalError::fatal_error("Unknown graphics API type.  Cannot return shader compiler.");
	std::shared_ptr<IShaderCompiler> shader_compiler = nullptr;
	return shader_compiler;
	
}
