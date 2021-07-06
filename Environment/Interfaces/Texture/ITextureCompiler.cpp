#include "ITextureCompiler.h"
#include "../../Utility/FatalError.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../OpenGL/Texture/OpenGLTextureCompiler.h"

ITextureCompiler::ITextureCompiler(const ITextureLoader& texture_loader)
	:m_texture_loading_data{ texture_loader.load() }{
}

std::unique_ptr<ITextureCompiler> ITextureCompiler::create_compiler(const ITextureLoader& texture_loader){

	std::unique_ptr<ITextureCompiler> texture_compiler = nullptr;
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		texture_compiler = std::make_unique<OpenGL::OpenGLTextureCompiler>(texture_loader);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan texture compiler does not exist!.");
	} else{
		FatalError::fatal_error("Unknown graphics API type.  Cannot return texture compiler.");
	}
	
	return texture_compiler;
	
}
