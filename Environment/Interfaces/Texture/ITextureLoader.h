#pragma once
#include "../../Neutral/Texture/TextureLoadingData.h"
#include <unordered_map>
#include <memory>

class ITextureLoader{
	
public:
	virtual ~ITextureLoader() = default;
	
	// Returns a pointer to the image data in memory
	[[nodiscard]] virtual TextureLoadingData load() = 0;
	[[nodiscard]] virtual std::unordered_map<std::string, std::shared_ptr<ITextureLoader>> create_cubemap_loader() = 0;
	
};
