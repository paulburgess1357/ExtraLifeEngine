#pragma once
#include "IMesh.h"
#include "../Vertex.h"
#include "../../Environment/OpenGL/Texture/OpenGLTextureHandler.h"
#include <vector>

namespace OpenGL{

	class OpenGLMesh : public IMesh {

	public:

		OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		void draw() const override;
		void destroy() override;
		
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indicies;

	private:
		void setup();
		
		unsigned int m_vao;
		unsigned int m_vbo;
		unsigned int m_ebo;
		
	};
	
} // namespace OpenGL



