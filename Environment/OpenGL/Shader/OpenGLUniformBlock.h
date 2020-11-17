#pragma once
#include "../../Interfaces/Shader/IShaderUniformBlock.h"

namespace OpenGL{

	class OpenGLUniformBlock : public IShaderUniformBlock {

	public:

		void create_projection_view_block() override;
		void link_projection_view_block_to_shader(std::shared_ptr<IShaderProgram> shader_program) override;	
		void set_projection_view_block_matrix_values(Camera& camera) const override;

		void create_camera_position_block() override;
		void link_camera_position_block_to_shader(std::shared_ptr<IShaderProgram> shader_program) override;
		void set_camera_position_block_vector_values(Camera& camera) const override;
		
		void update(Camera& camera) const override;
		void destroy() const override;
		
	};
	
} //namespace OpenGL



