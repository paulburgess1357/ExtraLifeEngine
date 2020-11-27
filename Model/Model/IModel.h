#pragma once
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>

class IModel{
	
public:
	IModel(const std::shared_ptr<IShaderProgram>& shader_program);
	virtual ~IModel() = default;	
	virtual void draw() const = 0;
	virtual void destroy() = 0;
	
protected:
	std::shared_ptr<IShaderProgram> m_shader_program;
	
};
