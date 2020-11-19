#include "ITextureCompiler.h"
#include "../../Utility/FatalError.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../OpenGL/Texture/OpenGLTextureCompiler.h"

ITextureCompiler::ITextureCompiler(const std::shared_ptr<ITextureLoader>& texture_loader)
	:m_texture_loading_data{ texture_loader->load() } {
}

std::shared_ptr<ITextureCompiler> ITextureCompiler::create_compiler(const std::shared_ptr<ITextureLoader>& texture_loader){

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLTextureCompiler>(texture_loader);
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<ITextureCompiler> texture_compiler = nullptr;
		FatalError::fatal_error("Vulkan texture compiler does not exist!.");
		return texture_compiler;
	}

	FatalError::fatal_error("Unknown graphics API type.  Cannot return texture compiler.");
	std::shared_ptr<ITextureCompiler> texture_compiler = nullptr;
	return texture_compiler;
	
}
