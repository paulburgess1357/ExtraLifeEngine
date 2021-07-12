#pragma once
#include "../../Environment/Interfaces/Texture/ITextureLoader.h"
#include "../../Environment/Interfaces/Texture/ICubeMapCompiler.h"
#include <glad/glad.h>

namespace OpenGL{
	
	class OpenGLCubeMapCompiler : public ICubeMapCompiler {
		
	public:
		OpenGLCubeMapCompiler(std::unordered_map<std::string, std::unique_ptr<ITextureLoader>>& texture_loaders);
		std::unique_ptr<ITexture> compile(const std::string& cubemap_name) override;

	private:		
		static void set_texture_parameters();
		void generate_textures() const;
	};
	
} // namespace OpenGL
