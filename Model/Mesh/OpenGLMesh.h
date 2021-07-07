#pragma once
#include "IMesh.h"
#include "../Vertex.h"
#include "../../Environment/Interfaces/Texture/ITexture.h"
#include "../../Environment/OpenGL/Texture/OpenGLTextureHandler.h"
#include <vector>

namespace OpenGL{

	class OpenGLMesh : public IMesh {

	public:
		OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, IShaderProgram& shader_program);
		void destroy() override;

		void attach_diffuse_texture(const ITexture& texture) override;
		void attach_normal_texture(const ITexture& texture) override;
		void attach_specular_texture(const ITexture& texture, const float shininess = 16.0f) override;

		[[nodiscard]] unsigned int get_vao() const override;
		
	private:
		void setup();
		
		unsigned int m_vao;
		unsigned int m_vbo;
		unsigned int m_ebo;				
	};
	
} // namespace OpenGL
