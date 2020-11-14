#pragma once
#include "../../Interfaces/Shader/IShaderUniformBlock.h"

namespace OpenGL{

	class OpenGLUniformBlock : public IShaderUniformBlock {

	public:
		void create_projection_view_block() override;
		void link_projection_view_block_to_shader(std::shared_ptr<IShaderProgram> shader_program) override;	
		void set_projection_view_block_matrix_values(Camera& camera) const override;
		void update(Camera& camera) const override;
		void destroy() const override;
		
	};
	
} //namespace OpenGL



