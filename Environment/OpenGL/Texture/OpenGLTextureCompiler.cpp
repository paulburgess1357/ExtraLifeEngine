#include "OpenGLTextureCompiler.h"
#include "OpenGLTexture.h"
#include "../Texture/TextureFormatFinder.h"
#include "../../Utility/Print.h"
#include "../../Utility/SBTIUtilities.h"
#include "../../Neutral/Texture/TextureLoaderFromFile.h"
#include "../../ResourceManagement/GraphicsConstants.h"
#include <glad/glad.h>

OpenGL::OpenGLTextureCompiler::OpenGLTextureCompiler(const ITextureLoader& texture_loader)
	:ITextureCompiler{ texture_loader }{
}

std::unique_ptr<ITexture> OpenGL::OpenGLTextureCompiler::compile(const bool apply_gamma_correction) {

	// Gamma correction will be applied when BOTH apply_gamma_correction = true
	// and gamma correction is enabled: glEnable(GL_FRAMEBUFFER_SRGB);
	// If apply_gamma_correction was true but GL_FRAMEBUFFER_SRGB was not
	// enabled, no gamma correction will be applied.  The apply_gamma_correction
	// parameter is really to allow us to say NOT to apply gamma correction
	// to lighting maps such as normal maps and specular maps.
	
	unsigned int texture_handle{ GraphicsConstants::UNINITIALIZED_VALUE };

	// Store w/ OpenGL & bind
	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_2D, texture_handle);

	set_texture_parameters();
	generate_texture(apply_gamma_correction);
	generate_mipmaps();

	// Unbind	
	glBindTexture(GL_TEXTURE_2D, 0);

	// Place handle in OpenGL texture class
	Print::print("Texture Handle: " + std::to_string(texture_handle));
	std::unique_ptr<ITexture> texture = std::make_unique<OpenGL::OpenGLTexture>(texture_handle, m_texture_loading_data.m_texture_name);
	return texture;
}

void OpenGL::OpenGLTextureCompiler::set_texture_parameters() {

	//'S' is the x axis, 'T' is y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Resize parameters (linear/nearest neighbor)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void OpenGL::OpenGLTextureCompiler::generate_texture(const bool apply_gamma_correction) const {
	const GLenum internal_format = TextureFormatFinder::get_texture_internal_format(m_texture_loading_data.m_components);
	const GLenum format = TextureFormatFinder::get_texture_standard_format(m_texture_loading_data.m_components);
	TextureFormatFinder::print_gamma_correction_applied(apply_gamma_correction);
	
	if(apply_gamma_correction){
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_texture_loading_data.m_width, m_texture_loading_data.m_height, 0, format, GL_UNSIGNED_BYTE, m_texture_loading_data.m_image_data);
	} else{
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_texture_loading_data.m_width, m_texture_loading_data.m_height, 0, format, GL_UNSIGNED_BYTE, m_texture_loading_data.m_image_data);
	}
	
	SBTIUtilities::free_image(m_texture_loading_data.m_image_data);
}

void OpenGL::OpenGLTextureCompiler::generate_mipmaps() {
	glGenerateMipmap(GL_TEXTURE_2D);
}


