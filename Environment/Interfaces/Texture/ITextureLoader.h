#pragma once
#include "../../Neutral/Texture/TextureLoadingData.h"

class ITextureLoader{
	
public:
	virtual ~ITextureLoader() = default;
	
	// Returns a pointer to the image date in memory
	[[nodiscard]] virtual TextureLoadingData load() = 0;
	
};
