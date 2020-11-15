#pragma once
#include "ITexture.h"
#include "ITextureLoader.h"
#include "../../Neutral/Texture/TextureLoadingData.h"
#include <memory>

class ITextureCompiler {

public:
	ITextureCompiler(const std::shared_ptr<ITextureLoader>& texture_loader)
		:m_texture_loading_data{ texture_loader->load() }{
	}

	virtual ~ITextureCompiler() = default;
	[[nodiscard]] virtual std::shared_ptr<ITexture> compile() = 0;
	
protected:
	TextureLoadingData m_texture_loading_data;
		
};
