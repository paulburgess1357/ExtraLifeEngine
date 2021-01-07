#pragma once

#define CX 16
#define CY 16
#define CZ 16

#include <cstdint>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "../Environment/OpenGL/Shader/OpenGLShaderProgram.h"

typedef glm::tvec4<GLbyte> byte4;

namespace OpenGL{
	
	class OpenGLChunk {

	public:
		OpenGLChunk(const glm::vec3& starting_world_position, const std::shared_ptr<OpenGLShaderProgram>& shader_program);
		~OpenGLChunk();

		uint8_t get(const int x, const int y, const int z) const;
		void set(const int x, const int y, const int z, uint8_t type);
		void initialize();
		void update();
		void render();

	private:
		uint8_t m_block_types[CX][CY][CZ];		
		unsigned int m_vbo;
		unsigned int m_vao;
		int m_vertex_qty;
		bool m_contents_changed;
		std::shared_ptr<OpenGLShaderProgram> m_shader_program;
	};
	
} //namespace OpenGL



