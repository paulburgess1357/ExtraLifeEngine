#include "OpenGLTextureCompiler.h"
#include "OpenGLTexture.h"
#include "../../Neutral/Texture/TextureLoaderFromFile.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"

OpenGL::OpenGLTextureCompiler::OpenGLTextureCompiler(const std::shared_ptr<ITextureLoader>& texture_loader)
	:ITextureCompiler{ texture_loader }{	
}

std::shared_ptr<ITexture> OpenGL::OpenGLTextureCompiler::compile() {
	Print::print("Compiling Texture");
	std::shared_ptr<ITexture> texture = compile_texture();
	TextureLoaderFromFile::free_loaded_texture_data(m_texture_loading_data);
	return texture;	
}

std::shared_ptr<ITexture> OpenGL::OpenGLTextureCompiler::compile_texture() const{

	unsigned int texture_handle{ 99 }; // Bug: Possible bug here.... not sure if this goes out of scope if open gl holds the texture number (problaby not since its copied to my constructor for the Texture Program)

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
	std::shared_ptr<ITexture> texture = std::make_shared<OpenGL::OpenGLTexture>(texture_handle);
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
	GLenum format = get_texture_format();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texture_loading_data.m_width, m_texture_loading_data.m_height, 0, format, GL_UNSIGNED_BYTE, m_texture_loading_data.m_image_data);
}

GLenum OpenGL::OpenGLTextureCompiler::get_texture_format() const{
	GLenum format { 0 }; // Bug - possible bug here.... not sure ------------------------------------------------------------------------------------------------------------------------------------------------------------
	if (m_texture_loading_data.m_components == 1) {
		format = GL_RED;
	} else if (m_texture_loading_data.m_components == 3) {
		format = GL_RGB;
	} else if (m_texture_loading_data.m_components == 4) {
		format = GL_RGBA;
	} else {
		FatalError::fatal_error("Unknown component number in load_texture function!");
	}
	return format;
}

void OpenGL::OpenGLTextureCompiler::generate_mipmaps() {
	glGenerateMipmap(GL_TEXTURE_2D);
}
