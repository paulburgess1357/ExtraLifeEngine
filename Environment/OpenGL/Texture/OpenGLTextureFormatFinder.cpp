#include "OpenGLTextureFormatFinder.h"
#include "../../../Environment/Neutral/FrameBuffer/FrameBufferHandler.h"
#include "../../../Utility/Print.h"
#include "../../../Utility/FatalError.h"

// Khronos:
// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
// void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data)

GLenum OpenGL::OpenGLTextureFormatFinder::get_texture_internal_format(const unsigned int component_num){

	// The gamma correction format will only be returned if gamma correction
	// is active based on a custom gamma framebuffer

	if(FrameBufferHandler::gamma_correction_enabled() || glIsEnabled(GL_FRAMEBUFFER_SRGB)){
		// Return internal gamma correction format		
		return get_texture_gamma_format(component_num);
	}	
	return get_texture_standard_format(component_num);
}


GLenum OpenGL::OpenGLTextureFormatFinder::get_texture_gamma_format(const unsigned int component_num){

	// This returns internal texture format for when gamma correction is
	GLenum format{ 0 };
	if (component_num == 1) {
		Print::print("RED Format");
		format = GL_RED;
	} else if (component_num == 3) {
		Print::print("RGB Format");
		format = GL_SRGB;
	} else if (component_num == 4) {
		Print::print("RGBA Format");
		format = GL_SRGB_ALPHA;
	} else {
		FatalError::fatal_error("Unknown component number in load_texture function!");
	}
	return format;
	
}

GLenum OpenGL::OpenGLTextureFormatFinder::get_texture_standard_format(const unsigned int component_num){

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
		FatalError::fatal_error("Unknown component number in load_texture function!");
	}
	return format;
	
}

void OpenGL::OpenGLTextureFormatFinder::print_gamma_correction_applied(const bool gamma_correction_applied){
	if ((FrameBufferHandler::gamma_correction_enabled() && gamma_correction_applied) || (glIsEnabled(GL_FRAMEBUFFER_SRGB) && gamma_correction_applied)) {
		Print::print("Gamma Correction Applied");
	}
}
