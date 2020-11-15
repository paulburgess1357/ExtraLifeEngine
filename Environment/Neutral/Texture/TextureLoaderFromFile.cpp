#include "TextureLoaderFromFile.h"
#include "../../Utility/FatalError.h"

#define STB_IMAGE_IMPLEMENTATION // Both of these must only exist
#include "stb_image/stb_image.h" // in a single file (per source doc)

TextureLoaderFromFile::TextureLoaderFromFile(const std::string& texture_path, const bool flip_texture)
	:m_flip_texture{ flip_texture },
	m_texture_path{ texture_path }{
	
}

TextureLoadingData TextureLoaderFromFile::load() {
	
	TextureLoadingData texture_loading_data;

	stbi_set_flip_vertically_on_load(m_flip_texture);
	texture_loading_data.m_image_data = stbi_load(m_texture_path.c_str(), &texture_loading_data.m_width, &texture_loading_data.m_height, &texture_loading_data.m_components, 0);
	
	check_image_data(texture_loading_data.m_image_data);
	return texture_loading_data;
}

void TextureLoaderFromFile::check_image_data(void* image_data) const{
	if(image_data == nullptr){
		FatalError::fatal_error("Image data failed to load for: " + m_texture_path);
	}
}

void TextureLoaderFromFile::free_loaded_texture_data(TextureLoadingData texture_loading_data) {
	stbi_image_free(texture_loading_data.m_image_data);
}