#pragma once

#define CX 16
#define CY 16
#define CZ 16

#include "WorldPosition.h"
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <cstdint>
#include <glad/glad.h>
#include <memory>

typedef glm::tvec4<GLbyte> byte4;

namespace OpenGL{
	
	class OpenGLChunk {

	public:
		OpenGLChunk(const WorldPosition& starting_world_position, const std::shared_ptr<IShaderProgram>& shader_program);
		~OpenGLChunk();

		uint8_t get(const int x, const int y, const int z) const;
		void set(const int x, const int y, const int z, uint8_t type);		
		void update();
		void render() const;

	private:
		void initialize();
		
		uint8_t m_block_types[CX][CY][CZ];		
		unsigned int m_vbo;
		unsigned int m_vao;
		
		int m_vertex_qty;
		bool m_update_required;

		glm::mat4 m_model_matrix;
		std::shared_ptr<IShaderProgram> m_shader_program;
	};
	
} //namespace OpenGL



