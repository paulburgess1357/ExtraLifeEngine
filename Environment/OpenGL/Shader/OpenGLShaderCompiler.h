#pragma once
#include "../../Environment/Interfaces/Shader/IShaderLoader.h"
#include "../../Environment/Interfaces/Shader/IShaderCompiler.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "../../Environment/Neutral/Shader/ShaderType.h"
#include <memory>
#include <string>

namespace OpenGL{
	
	class OpenGLShaderCompiler : public IShaderCompiler {

	public:
		OpenGLShaderCompiler(const std::shared_ptr<IShaderLoader>& shader_loader);
		[[nodiscard]] std::shared_ptr<IShaderProgram> compile() const override;
	
	private:
		static unsigned int compile_glsl_shader(const std::string& shader_glsl_code, const ShaderType shader_type);
		[[nodiscard]] std::shared_ptr<IShaderProgram> compile_shader_program(const unsigned int vertex_shader_id, const unsigned int fragment_shader_id) const;
	
		static void check_vertex_frament_errors(const unsigned int shader_id);
		static void check_shader_program_errors(const unsigned int shader_handle);
	};
	
} // namespace OpenGL



