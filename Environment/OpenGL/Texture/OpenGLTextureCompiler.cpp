#include "OpenGLTextureCompiler.h"
#include "OpenGLTexture.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include "../../Utility/SBTIUtilities.h"
#include "../../Neutral/Texture/TextureLoaderFromFile.h"
#include "../../ResourceManagement/GraphicsConstants.h"

OpenGL::OpenGLTextureCompiler::OpenGLTextureCompiler(const ITextureLoader& texture_loader)
	:ITextureCompiler{ texture_loader }{
}

std::unique_ptr<ITexture> OpenGL::OpenGLTextureCompiler::compile() {

	unsigned int texture_handle{ GraphicsConstants::UNINITIALIZED_VALUE };

	// Store w/ OpenGL & bind
	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_2D, texture_handle);

	set_texture_parameters();
	generate_texture();
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

void OpenGL::OpenGLTextureCompiler::generate_texture() const {
	GLenum format = get_texture_format(m_texture_loading_data.m_components);
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_texture_loading_data.m_width, m_texture_loading_data.m_height, 0, format, GL_UNSIGNED_BYTE, m_texture_loading_data.m_image_data);
	SBTIUtilities::free_image(m_texture_loading_data.m_image_data);
}

GLenum OpenGL::OpenGLTextureCompiler::get_texture_format(const unsigned int component_num) {
	GLenum format { 0 };
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
		FatalError::fatal_error("Unknown component number in load_texture function!");
	}
	return format;
}

void OpenGL::OpenGLTextureCompiler::generate_mipmaps() {
	glGenerateMipmap(GL_TEXTURE_2D);
}
