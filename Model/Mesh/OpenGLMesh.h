#pragma once
#include "IMesh.h"
#include "../Vertex.h"
#include "../../Environment/OpenGL/Texture/OpenGLTextureHandler.h"
#include <vector>

namespace OpenGL{

	class OpenGLMesh : public IMesh {

	public:
		OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::shared_ptr<IShaderProgram>& shader_program);
		void destroy() override;

		void attach_diffuse_texture(const std::string& texture_name) override;
		void attach_normal_texture(const std::string& texture_name) override;
		void attach_specular_texture(const std::string& texture_name, const float shininess = 16.0f) override;

		[[nodiscard]] unsigned int get_vao() const override;
		
	private:
		void setup();
		
		unsigned int m_vao;
		unsigned int m_vbo;
		unsigned int m_ebo;				
	};
	
} // namespace OpenGL
