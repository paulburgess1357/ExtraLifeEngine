#include "IModel.h"

IModel::IModel(const std::shared_ptr<IShaderProgram>& shader_program)
	:m_shader_program{ shader_program }{
	
}
