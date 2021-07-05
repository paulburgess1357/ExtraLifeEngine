#pragma once
#include "../../Neutral/Texture/TextureLoadingData.h"
#include <unordered_map>
#include <memory>
#include <string>

class ITextureLoader{
	
public:
	ITextureLoader(std::string texture_name)
		:m_texture_name{ std::move(texture_name) }{		
	}
	
	virtual ~ITextureLoader() = default;
	
	// Returns a pointer to the image data in memory
	[[nodiscard]] virtual TextureLoadingData load() = 0;
	[[nodiscard]] virtual std::unordered_map<std::string, std::shared_ptr<ITextureLoader>> create_cubemap_loader() = 0;

protected:
	std::string m_texture_name;
	
};
