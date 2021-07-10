#pragma once
#include "../../Interfaces/Shader/IShaderProgram.h"
#include "../../Interfaces/Shader/IShaderUniformBlock.h"

namespace OpenGL{

	class OpenGLUniformBlock : public IShaderUniformBlock {

	public:
		OpenGLUniformBlock();
		OpenGLUniformBlock(ProjectionMatrix* projection_matrix);

		static void create_projection_view_block();
		static void link_projection_view_block_to_shader(IShaderProgram& shader_program);
		void set_projection_view_block_matrix_values(Camera& camera) const override;

		static void create_camera_position_block();
		static void link_camera_position_block_to_shader(IShaderProgram& shader_program);
		void set_camera_position_block_vector_values(Camera& camera) const override;
		
		void update(Camera& camera) const override;
		void destroy() const override;
		
	};
	
} //namespace OpenGL
