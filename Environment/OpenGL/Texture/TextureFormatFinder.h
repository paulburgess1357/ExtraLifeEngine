#pragma once
#include <glad/glad.h>

class TextureFormatFinder{
public:
	static GLenum get_texture_internal_format(const unsigned int component_num);
	static GLenum get_texture_standard_format(const unsigned int component_num);
private:
	static GLenum get_texture_gamma_format(const unsigned int component_num);	
};