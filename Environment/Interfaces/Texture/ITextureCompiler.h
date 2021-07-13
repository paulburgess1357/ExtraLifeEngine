#pragma once
#include "ITexture.h"
#include "ITextureLoader.h"
#include "../../Neutral/Texture/TextureLoadingData.h"
#include <memory>

class ITextureCompiler {

public:
	ITextureCompiler(const ITextureLoader& texture_loader);

	virtual ~ITextureCompiler() = default;
	[[nodiscard]] virtual std::unique_ptr<ITexture> compile(const bool apply_gamma_correction) = 0;
	[[nodiscard]] static std::unique_ptr<ITextureCompiler> create_compiler(const ITextureLoader& texture_loader);
	
protected:
	TextureLoadingData m_texture_loading_data;
		
};
