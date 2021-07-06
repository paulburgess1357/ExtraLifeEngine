#include "OpenGLShaderCompiler.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLUniformBlock.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include <glad/glad.h>

OpenGL::OpenGLShaderCompiler::OpenGLShaderCompiler(const IShaderLoader& shader_loader)
	:IShaderCompiler(shader_loader){	
}

std::unique_ptr<IShaderProgram> OpenGL::OpenGLShaderCompiler::compile() const{	
	
	Print::print("Compiling Shader");

	const unsigned int vertex_shader_id = compile_glsl_shader(m_vertex_fragment_strings.first, ShaderType::VERTEX);
	const unsigned int fragment_shader_id = compile_glsl_shader(m_vertex_fragment_strings.second, ShaderType::FRAGMENT);	

	// Create program to link the shaders		
	std::unique_ptr<IShaderProgram> shader_program = compile_shader_program(vertex_shader_id, fragment_shader_id);
	
	// Link uniform blocks (used across all shaders)
	OpenGLUniformBlock opengl_uniform_block_allocator;
	opengl_uniform_block_allocator.link_projection_view_block_to_shader(*shader_program);
	opengl_uniform_block_allocator.link_camera_position_block_to_shader(*shader_program);

	// Initialize Handlers
	shader_program->init_texture_handler();	
	shader_program->init_light_handler();

	// Set light uniforms to -1 (inactive)
	shader_program->set_uniform("active_dirlight_qty", -1);
	shader_program->set_uniform("active_pointlight_qty", -1);
		
	return shader_program;		
}

unsigned int OpenGL::OpenGLShaderCompiler::compile_glsl_shader(const std::string& shader_glsl_code, const ShaderType shader_type){
	const char* shader_code_ptr = shader_glsl_code.c_str();
	unsigned int shader_id{ 99 };

	if(shader_type == ShaderType::VERTEX){
		Print::print("Creating Vertex Shader");
		shader_id = glCreateShader(GL_VERTEX_SHADER);
	} else{
		Print::print("Creating Fragment Shader");
		shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	
	glShaderSource(shader_id, 1, &shader_code_ptr, nullptr);
	glCompileShader(shader_id);
	
	check_vertex_frament_errors(shader_id);

	return shader_id;
}

void OpenGL::OpenGLShaderCompiler::check_vertex_frament_errors(const unsigned int shader_id) {
	int success{ 0 };
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint error_length{ 0 };
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &error_length);

		std::string error_string(error_length, ' ');
		glGetShaderInfoLog(shader_id, error_length, &error_length, &error_string[0]);
		FatalError::fatal_error("Shaders(vertex/fragment) Failed to Compile: " + error_string);
	}
}

std::unique_ptr<IShaderProgram> OpenGL::OpenGLShaderCompiler::compile_shader_program(const unsigned int vertex_shader_id, const unsigned int fragment_shader_id) const{

	unsigned int shader_program_handle = glCreateProgram();
	glAttachShader(shader_program_handle, vertex_shader_id);
	glAttachShader(shader_program_handle, fragment_shader_id);
	glLinkProgram(shader_program_handle);

	Print::print("Shader Handle: " + std::to_string(shader_program_handle));
	std::unique_ptr<IShaderProgram> shader_program = std::make_unique<OpenGL::OpenGLShaderProgram>(shader_program_handle);

	Print::print("Checking Shader Program for Errors");
	check_shader_program_errors(shader_program_handle);

	// After successful link detach and delete
	glDetachShader(shader_program_handle, vertex_shader_id);
	glDetachShader(shader_program_handle, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return shader_program;
}

void OpenGL::OpenGLShaderCompiler::check_shader_program_errors(const unsigned int shader_handle){
	int success{ 0 };
	glGetProgramiv(shader_handle, GL_LINK_STATUS, &success);
	if (!success) {
		GLint error_length{ 0 };
		glGetProgramiv(shader_handle, GL_INFO_LOG_LENGTH, &error_length);

		std::string error_string(error_length, ' ');
		glGetProgramInfoLog(shader_handle, error_length, &error_length, &error_string[0]);
		FatalError::fatal_error("OpenGLShaderProgram Program Failed to Link: " + error_string);
	}
}
