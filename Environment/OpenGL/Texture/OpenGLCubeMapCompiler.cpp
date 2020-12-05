#include "OpenGLCubeMapCompiler.h"
#include "OpenGLTexture.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include "../../Utility/SBTIUtilities.h"
#include "../../Neutral/Texture/TextureLoaderFromFile.h"

OpenGL::OpenGLCubeMapCompiler::OpenGLCubeMapCompiler(std::unordered_map<std::string, std::shared_ptr<ITextureLoader>>& texture_loaders)
	:ICubeMapCompiler{ texture_loaders }{	
}

std::shared_ptr<ITexture> OpenGL::OpenGLCubeMapCompiler::compile(){

	unsigned int texture_handle{ 99 };

	// Store w/ OpenGL & bind
	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_handle);
	
	set_texture_parameters();
	generate_textures();
	
	// Place handle in OpenGL texture class
	Print::print("Texture Handle: " + std::to_string(texture_handle));
	std::shared_ptr<ITexture> texture = std::make_shared<OpenGL::OpenGLTexture>(texture_handle);
	return texture;
	
}

void OpenGL::OpenGLCubeMapCompiler::generate_textures() const{

	for (unsigned int i = 0; i < m_texture_loading_data.size(); i++) {
		
		const TextureLoadingData texture_loading_data = m_texture_loading_data.at(i);		
		const GLenum texture_format = get_texture_format(texture_loading_data.m_components);
		
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, texture_format, texture_loading_data.m_width, texture_loading_data.m_height, 0, texture_format, GL_UNSIGNED_BYTE, texture_loading_data.m_image_data);
		SBTIUtilities::free_image(texture_loading_data.m_image_data);
		
	}	
}

void OpenGL::OpenGLCubeMapCompiler::set_texture_parameters(){
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


GLenum OpenGL::OpenGLCubeMapCompiler::get_texture_format(const unsigned int component_num) {
	GLenum format{ 0 };
	if (component_num == 1) {
		Print::print("RED Format");
		format = GL_RED;
	} else if (component_num == 3) {
		Print::print("RGB Format");
		format = GL_RGB;
	} else if (component_num == 4) {
		Print::print("RGBA Format");
		format = GL_RGBA;
	} else {
		FatalError::fatal_error("Unknown component number in cubemap get_texture_format function!");
	}
	return format;
}