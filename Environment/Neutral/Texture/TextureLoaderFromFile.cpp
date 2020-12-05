#include "TextureLoaderFromFile.h"
#include "../../Utility/FatalError.h"
#include "../../Utility/FileHandler.h"
#include "stb_image/stb_image.h"

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

std::unordered_map<std::string, std::shared_ptr<ITextureLoader>> TextureLoaderFromFile::create_cubemap_loaders(){
	
	std::vector<std::string> filenames = FileHandler::list_directory_filenames(m_texture_path);	
	const std::string extension = FileHandler::get_filename_extension(filenames.at(0));
	
	std::vector<std::string> expected_filenames{ "right", "left", "top", "bottom", "front", "back" };
	std::unordered_map<std::string, std::shared_ptr<ITextureLoader>> texture_loaders;

	for (const auto& expected_filename : expected_filenames) {
		texture_loaders[expected_filename] = std::make_shared<TextureLoaderFromFile>(m_texture_path + "/" + expected_filename + "." + extension, m_flip_texture);
	}

	return texture_loaders;
}
