#include "TextureFormatFinder.h"
#include "../../../Utility/Print.h"
#include "../../../Utility/FatalError.h"

// Khronos:
// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
// void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data)

GLenum TextureFormatFinder::get_texture_internal_format(const unsigned int component_num){

	// The gamma correction format will only be returned if gamma correction
	// is based on OpenGL's gamma correction format.  If gamma correction is
	// being manually entered at the final fragment shader rather than when
	// OpenGL & the window is initialized, this will not return the gamma
	// corrected format.  As such, if gamma correction is implemented in the
	// shader, this function likely needs to be updated to know if that is the
	// case.  E.g. get_texture_internal_format(bool gamma_correction_applied_in_shader)

	// Gamma correction should not be applied to textures used for lighting
	// (e.g. normal/specular maps should not apply it).  Gamma correction
	// should be used for coloring objects (e.g. diffuse).
	if(glIsEnabled(GL_FRAMEBUFFER_SRGB)){
		// Return internal gamma correction format		
		return get_texture_gamma_format(component_num);
	}	
	return get_texture_standard_format(component_num);
}


GLenum TextureFormatFinder::get_texture_gamma_format(const unsigned int component_num){

	// Specifies the number of color components in the texture. Must be one of
	// base internal formats given in Table 1, one of the sized internal formats
	// given in Table 2, or one of the compressed internal formats given in Table 3, below.

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

GLenum TextureFormatFinder::get_texture_standard_format(const unsigned int component_num){

	// Specifies the format of the pixel data. The following symbolic values are accepted:
	// GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER,
	// GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX,
	// GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.	
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

void TextureFormatFinder::print_gamma_correction_applied(const bool gamma_correction_applied){
	if (glIsEnabled(GL_FRAMEBUFFER_SRGB) && gamma_correction_applied) {
		Print::print("Gamma Correction Applied");
	}
}
