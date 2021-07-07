#pragma once
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"

struct ShaderComponent {
	ShaderComponent(IShaderProgram* shader_program)
		:m_shader_program{ shader_program } {
	}
	IShaderProgram* m_shader_program = nullptr;
};
