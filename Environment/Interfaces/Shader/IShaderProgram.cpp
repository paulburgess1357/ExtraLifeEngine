#include "IShaderProgram.h"

IShaderProgram::IShaderProgram(const unsigned int handle)
	:m_handle{ handle } {
}

[[nodiscard]] unsigned int IShaderProgram::get_handle() const {
	return m_handle;
}