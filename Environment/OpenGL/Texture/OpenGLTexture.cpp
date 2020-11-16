#include "OpenGLTexture.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include <glad/glad.h>

OpenGL::OpenGLTexture::OpenGLTexture(const unsigned handle)
	:ITexture{ handle } {
	
}

void OpenGL::OpenGLTexture::destroy() const{
	Print::print("Destroying Texture Handle: " + std::to_string(m_handle));
	glDeleteTextures(1, &m_handle);
}

