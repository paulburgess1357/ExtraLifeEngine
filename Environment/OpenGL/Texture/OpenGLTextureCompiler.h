#pragma once
#include "../../Interfaces/Texture/ITexture.h"
#include "../../Interfaces/Texture/ITextureLoader.h"
#include "../../Interfaces/Texture/ITextureCompiler.h"

namespace OpenGL{
	
	class OpenGLTextureCompiler : public ITextureCompiler {

	public:
		OpenGLTextureCompiler(const ITextureLoader& texture_loader);
		[[nodiscard]] std::unique_ptr<ITexture> compile(const bool apply_gamma_correction) override;

	private:
		static void set_texture_parameters();
		void generate_texture(const bool apply_gamma_correction) const;
		static void generate_mipmaps();
				
	};
	
} //namespace OpenGL
