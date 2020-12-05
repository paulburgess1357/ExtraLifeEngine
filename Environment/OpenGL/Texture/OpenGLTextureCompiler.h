#pragma once
#include "../../Interfaces/Texture/ITexture.h"
#include "../../Interfaces/Texture/ITextureLoader.h"
#include "../../Interfaces/Texture/ITextureCompiler.h"
#include <glad/glad.h>

namespace OpenGL{
	
	class OpenGLTextureCompiler : public ITextureCompiler {

	public:
		OpenGLTextureCompiler(const std::shared_ptr<ITextureLoader>& texture_loader);
		[[nodiscard]] std::shared_ptr<ITexture> compile() override;

	private:
		[[nodiscard]] std::shared_ptr<ITexture> compile_texture() const;
		static void set_texture_parameters();
		void generate_texture() const;
		static GLenum get_texture_format(const unsigned int component_num);		
		static void generate_mipmaps();
				
	};
	
} //namespace OpenGL


