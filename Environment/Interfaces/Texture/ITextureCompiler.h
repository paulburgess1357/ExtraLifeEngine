#pragma once
#include "ITexture.h"
#include "ITextureLoader.h"
#include "../../Neutral/Texture/TextureLoadingData.h"
#include <memory>

class ITextureCompiler {

public:
	ITextureCompiler(const std::shared_ptr<ITextureLoader>& texture_loader);

	virtual ~ITextureCompiler() = default;
	[[nodiscard]] virtual std::unique_ptr<ITexture> compile() = 0;
	[[nodiscard]] static std::shared_ptr<ITextureCompiler> create_compiler(const std::shared_ptr<ITextureLoader>& texture_loader);
	
protected:
	TextureLoadingData m_texture_loading_data;
		
};
