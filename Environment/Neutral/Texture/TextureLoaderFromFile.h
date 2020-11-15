#pragma once
#include "../../Interfaces/Texture/ITextureLoader.h"
#include "../Texture/TextureLoadingData.h"
#include <string>

class TextureLoaderFromFile : public ITextureLoader {
	
public:
	TextureLoaderFromFile(const std::string& texture_path, const bool flip_texture);
	[[nodiscard]] TextureLoadingData load() override;

	// Loaded STBI texture data must be freed (it is subsequently handled by OpenGL/Vulkan)
	static void free_loaded_texture_data(TextureLoadingData texture_loading_data);
		
private:
	void check_image_data(void* image_data) const;
	
	bool m_flip_texture;
	std::string m_texture_path;
	
};

