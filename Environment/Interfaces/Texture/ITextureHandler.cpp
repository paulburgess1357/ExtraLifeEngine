#include "ITextureHandler.h"

ITextureHandler::ITextureHandler()
	:m_shader_program{ nullptr }{
}

ITextureHandler::ITextureHandler(IShaderProgram& shader_program)
	:m_shader_program{ &shader_program }{	
}

void ITextureHandler::set_shader_program(IShaderProgram& shader_program){
	m_shader_program = &shader_program;
}
