#pragma once
#include "../../Interfaces/Texture/ITextureLoader.h"
#include "../Texture/TextureLoadingData.h"
#include <string>
#include <memory>
#include <unordered_map>

class TextureLoaderFromFile : public ITextureLoader {
	
public:
	TextureLoaderFromFile(std::string texture_name, std::string texture_path, const bool flip_texture);
	[[nodiscard]] TextureLoadingData load() const override;
	[[nodiscard]] std::unordered_map<std::string, std::unique_ptr<ITextureLoader>> create_cubemap_loader() override;
		
private:
	void check_image_data(void* image_data) const;
	
	std::string m_texture_path;
	bool m_flip_texture;	
};