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

std::unique_ptr<ITexture> OpenGL::OpenGLCubeMapCompiler::compile(const std::string& cubemap_name, const bool apply_gamma_correction){

	// Gamma correction will be applied when BOTH apply_gamma_correction = true
	// and gamma correction is enabled: FrameBufferHandler::gamma_correction_enabled();
	// If apply_gamma_correction was true but GL_FRAMEBUFFER_SRGB was not
	// enabled, no gamma correction will be applied.  The apply_gamma_correction
	// parameter is really to allow us to say NOT to apply gamma correction
	// to lighting maps such as normal maps and specular maps.
	
	unsigned int texture_handle{ GraphicsConstants::UNINITIALIZED_VALUE };

	// Store w/ OpenGL & bind
	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_handle);
	
	set_texture_parameters();
	generate_textures(apply_gamma_correction);
	
	// Place handle in OpenGL texture class
	Print::print("Texture Handle: " + std::to_string(texture_handle));
	std::unique_ptr<ITexture> texture = std::make_unique<OpenGL::OpenGLTexture>(texture_handle, cubemap_name);
	return texture;
	
}

void OpenGL::OpenGLCubeMapCompiler::generate_textures(const bool apply_gamma_correction) const{

	for (unsigned int i = 0; i < m_texture_loading_data.size(); i++) {		
		const TextureLoadingData texture_loading_data = m_texture_loading_data.at(i);		

		const GLenum internal_format = TextureFormatFinder::get_texture_internal_format(texture_loading_data.m_components);
		const GLenum format = TextureFormatFinder::get_texture_standard_format(texture_loading_data.m_components);
		TextureFormatFinder::print_gamma_correction_applied(apply_gamma_correction);
		
		if(apply_gamma_correction){
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, texture_loading_data.m_width, texture_loading_data.m_height, 0, format, GL_UNSIGNED_BYTE, texture_loading_data.m_image_data);
		} else{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, texture_loading_data.m_width, texture_loading_data.m_height, 0, format, GL_UNSIGNED_BYTE, texture_loading_data.m_image_data);
		}
				
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
