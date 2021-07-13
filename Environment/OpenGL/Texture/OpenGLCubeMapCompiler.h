#pragma once
#include "../../Environment/Interfaces/Texture/ITextureLoader.h"
#include "../../Environment/Interfaces/Texture/ICubeMapCompiler.h"

namespace OpenGL{
	
	class OpenGLCubeMapCompiler : public ICubeMapCompiler {
		
	public:
		OpenGLCubeMapCompiler(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders);
		std::unique_ptr<ITexture> compile(const std::string& cubemap_name, const bool apply_gamma_correction) override;

	private:		
		static void set_texture_parameters();
		void generate_textures(const bool apply_gamma_correction) const;
	};
	
} // namespace OpenGL
