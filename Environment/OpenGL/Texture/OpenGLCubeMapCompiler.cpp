#include "OpenGLCubeMapCompiler.h"
#include "OpenGLTexture.h"
#include "../Texture/TextureFormatFinder.h"
#include "../../Utility/Print.h"
#include "../../Utility/SBTIUtilities.h"
#include "../../ResourceManagement/GraphicsConstants.h"
#include "../../Neutral/Texture/TextureLoaderFromFile.h"
#include <glad/glad.h>

OpenGL::OpenGLCubeMapCompiler::OpenGLCubeMapCompiler(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders)
	:ICubeMapCompiler{ texture_loaders }{	
}

std::unique_ptr<ITexture> OpenGL::OpenGLCubeMapCompiler::compile(const std::string& cubemap_name){

	unsigned int texture_handle{ GraphicsConstants::UNINITIALIZED_VALUE };

	// Store w/ OpenGL & bind
	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_handle);
	
	set_texture_parameters();
	generate_textures();
	
	// Place handle in OpenGL texture class
	Print::print("Texture Handle: " + std::to_string(texture_handle));
	std::unique_ptr<ITexture> texture = std::make_unique<OpenGL::OpenGLTexture>(texture_handle, cubemap_name);
	return texture;
	
}

void OpenGL::OpenGLCubeMapCompiler::generate_textures() const{

	for (unsigned int i = 0; i < m_texture_loading_data.size(); i++) {		
		const TextureLoadingData texture_loading_data = m_texture_loading_data.at(i);		

		const GLenum internal_format = TextureFormatFinder::get_texture_internal_format(texture_loading_data.m_components);
		const GLenum format = TextureFormatFinder::get_texture_standard_format(texture_loading_data.m_components);		
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, texture_loading_data.m_width, texture_loading_data.m_height, 0, format, GL_UNSIGNED_BYTE, texture_loading_data.m_image_data);
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
