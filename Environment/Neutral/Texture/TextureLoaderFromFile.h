#pragma once
#include "../../Interfaces/Texture/ITextureLoader.h"
#include "../Texture/TextureLoadingData.h"
#include <string>
#include <memory>
#include <unordered_map>

class TextureLoaderFromFile : public ITextureLoader {
	
public:
	TextureLoaderFromFile(const std::string& texture_path, const bool flip_texture);
	[[nodiscard]] TextureLoadingData load() override;
	[[nodiscard]] std::unordered_map<std::string, std::shared_ptr<ITextureLoader>> create_cubemap_loaders() override;
		
private:
	void check_image_data(void* image_data) const;
	
	bool m_flip_texture;
	std::string m_texture_path;
	
};