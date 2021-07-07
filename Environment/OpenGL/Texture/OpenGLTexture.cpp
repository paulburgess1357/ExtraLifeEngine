#include "OpenGLTexture.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include <glad/glad.h>

OpenGL::OpenGLTexture::OpenGLTexture(const unsigned int handle, std::string texture_name)
	:ITexture{ handle, std::move(texture_name) } {
}

void OpenGL::OpenGLTexture::destroy() const{
	// Print::print("    - Destroying Texture Handle: " + std::to_string(m_handle) + "; Texture Name: " + m_texture_name);
	glDeleteTextures(1, &m_handle);
}
