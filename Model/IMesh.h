#pragma once
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>

class IMesh{
public:
private:
	std::shared_ptr<IShaderProgram> m_shader_program;

	
};