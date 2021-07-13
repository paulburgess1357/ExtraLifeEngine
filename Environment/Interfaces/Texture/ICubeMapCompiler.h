#pragma once
#include "ITexture.h"
#include "ITextureLoader.h"
#include "../../Neutral/Texture/TextureLoadingData.h"
#include <memory>
#include <unordered_map>

class ICubeMapCompiler{
	
public:
	ICubeMapCompiler(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders);
	virtual ~ICubeMapCompiler() = default;

	[[nodiscard]] virtual std::unique_ptr<ITexture> compile(const std::string& cubemap_name, const bool apply_gamma_correction) = 0;
	[[nodiscard]] static std::unique_ptr<ICubeMapCompiler> create_compiler(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders);

protected:
	std::vector<TextureLoadingData> m_texture_loading_data;

private:
	void load_texture_loading_data(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders);
};
