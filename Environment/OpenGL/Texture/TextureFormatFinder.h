#pragma once
#include <glad/glad.h>

class TextureFormatFinder{
public:
	static GLenum get_texture_internal_format(const unsigned int component_num);
	static GLenum get_texture_standard_format(const unsigned int component_num);
	static void print_gamma_correction_applied(const bool gamma_correction_applied);
private:
	static GLenum get_texture_gamma_format(const unsigned int component_num);	
};