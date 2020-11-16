#pragma once
#include <memory>
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"

struct ShaderComponent {
	
	ShaderComponent(const std::shared_ptr<IShaderProgram>& shader_program)
		:m_shader_program{ shader_program } {

	}
	std::shared_ptr<IShaderProgram> m_shader_program;
	
};
