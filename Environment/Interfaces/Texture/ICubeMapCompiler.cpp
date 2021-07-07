#include "ICubeMapCompiler.h"
#include "../../Utility/FatalError.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../Environment/OpenGL/Texture/OpenGLCubeMapCompiler.h"

ICubeMapCompiler::ICubeMapCompiler(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders){
	load_texture_loading_data(texture_loaders);
}

void ICubeMapCompiler::load_texture_loading_data(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders){

	// Data must be loaded in the following order:
	m_texture_loading_data.push_back(texture_loaders["right"]->load());
	m_texture_loading_data.push_back(texture_loaders["left"]->load());
	m_texture_loading_data.push_back(texture_loaders["top"]->load());
	m_texture_loading_data.push_back(texture_loaders["bottom"]->load());
	m_texture_loading_data.push_back(texture_loaders["front"]->load());
	m_texture_loading_data.push_back(texture_loaders["back"]->load());
	
}

std::unique_ptr<ICubeMapCompiler> ICubeMapCompiler::create_compiler(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders) {

	std::unique_ptr<ICubeMapCompiler> cubemap_compiler = nullptr;
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		cubemap_compiler = std::make_unique<OpenGL::OpenGLCubeMapCompiler>(texture_loaders);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan cubemap compiler does not exist!.");
	} else{
		FatalError::fatal_error("Unknown graphics API type.  Cannot return cubemap compiler.");
	}
	
	return cubemap_compiler;
}
