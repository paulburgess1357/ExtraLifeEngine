#include "ITextureHandler.h"

ITextureHandler::ITextureHandler()
	:m_shader_program{ nullptr } {
}

ITextureHandler::ITextureHandler(const std::shared_ptr<IShaderProgram>& shader_program)
	:m_shader_program(shader_program){	
}

void ITextureHandler::set_shader_program(const std::shared_ptr<IShaderProgram>& shader_program){
	m_shader_program = shader_program;
}
