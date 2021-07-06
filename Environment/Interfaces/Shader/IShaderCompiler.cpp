#include "IShaderCompiler.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/OpenGL/Shader/OpenGLShaderCompiler.h"

std::unique_ptr<IShaderCompiler> IShaderCompiler::create_compiler(const IShaderLoader& shader_loader){

	std::unique_ptr<IShaderCompiler> shader_compiler = nullptr;
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		shader_compiler = std::make_unique<OpenGL::OpenGLShaderCompiler>(shader_loader);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan shader compiler does not exist!.");
	} else{
		FatalError::fatal_error("Unknown graphics API type.  Cannot return shader compiler.");
	}
	
	return shader_compiler;
	
}
