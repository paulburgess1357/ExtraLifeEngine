#include "IShaderProgram.h"
#include <iostream>

IShaderProgram::IShaderProgram(const unsigned int handle)
	:m_handle{ handle } {
}

[[nodiscard]] unsigned int IShaderProgram::get_handle() const {
	return m_handle;
}

std::set<std::string> IShaderProgram::get_ignore_string_uniforms() {

	// These uniforms are ignored during the shader qc check via:
	// check_uniforms_in_shader_code_are_initialized();
	
	const std::set<std::string> ignore_strings{ "model_matrix", "normal_matrix", "projection_matrix" ,"camera_world_position", "view_matrix", "view_matrix_no_translation"};
	std::cout << "   - Ignoring:";

	for (const auto& ignore_str : ignore_strings) {
		std::cout << " | " + ignore_str;
	}
	std::cout << " | " << std::endl;
	return ignore_strings;
}