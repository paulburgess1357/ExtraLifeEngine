#pragma once
#include "../../Neutral/Texture/TextureLoadingData.h"
#include <unordered_map>
#include <memory>

class ITextureLoader{
	
public:
	virtual ~ITextureLoader() = default;
	
	// Returns a pointer to the image date in memory
	[[nodiscard]] virtual TextureLoadingData load() = 0;
	[[nodiscard]] std::unordered_map<std::string, std::shared_ptr<ITextureLoader>> virtual create_cubemap_loaders() = 0;
	
};
