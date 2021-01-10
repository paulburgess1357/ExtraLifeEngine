#pragma once
#define CX 15
#define CY 15
#define CZ 15

#include "WorldPosition.h"
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>

namespace OpenGL{
	
	class OpenGLChunk {

	public:
		OpenGLChunk(const WorldPosition& starting_world_position, const std::shared_ptr<IShaderProgram>& shader_program);
		~OpenGLChunk();

		[[nodiscard]] signed char get(const signed char x, const signed char y, const signed char z) const; 
		void set(const signed char x, const signed char y, const signed char z, const signed char type);
		void update();
		void render() const;
	private:
		
		void initialize_vbo_vao();
		void initialize_types();
		
		signed char m_block_types[CX][CY][CZ];		
		unsigned int m_vbo;
		unsigned int m_vao;
		
		int m_vertex_qty;
		bool m_update_required;

		glm::mat4 m_model_matrix;
		glm::mat3 m_normal_matrix;
		std::shared_ptr<IShaderProgram> m_shader_program;
	};
	
} //namespace OpenGL



