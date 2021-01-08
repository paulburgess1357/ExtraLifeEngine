#pragma once
#include "../../Environment/Interfaces/Texture/ITextureLoader.h"
#include "../../Environment/Interfaces/Texture/ICubeMapCompiler.h"
#include <glad/glad.h>

namespace OpenGL{
	
	class OpenGLCubeMapCompiler : public ICubeMapCompiler {
		
	public:
		OpenGLCubeMapCompiler(std::unordered_map<std::string, std::shared_ptr<ITextureLoader>>& texture_loaders);
		std::shared_ptr<ITexture> compile() override;

	private:		
		static void set_texture_parameters();
		void generate_textures() const;
		static GLenum get_texture_format(const unsigned int component_num);
		
	};
	
} // namespace OpenGL

