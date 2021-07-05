#include "OpenGLUniformBlock.h"
#include "../../Utility/Print.h"
#include "../../Matrix/ProjectionMatrix.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

OpenGL::OpenGLUniformBlock::~OpenGLUniformBlock(){
	// destroy();
}

void OpenGL::OpenGLUniformBlock::link_projection_view_block_to_shader(IShaderProgram& shader_program) {

	// Links a single shader to the uniform matrix data block (binding point 0)
	create_projection_view_block();
	IShaderUniformBlock::check_projection_view_block_created();
	Print::print("Linking shader program handle: '" + std::to_string(shader_program.get_handle()) + "' to uniform projection view block");

	// Uniform block index name is defined in GLSL shader code
	const unsigned int uniform_block_index = glGetUniformBlockIndex(shader_program.get_handle(), "uniform_matrices");

	// Set shader binding point (in this case binding point is 0 for all shaders)
	// ** Binding Point 0 **
	glUniformBlockBinding(shader_program.get_handle(), uniform_block_index, 0);
}

void OpenGL::OpenGLUniformBlock::create_projection_view_block(){

	// Allocates data to store uniform matrix data for both the perspective
	// and view matrices.  This will be used by all shaders linked via the
	// 'link_projection_view_block_to_shader' function.  Note that the shader must have the
	// uniform buffer object defined in the shader as well.

	if (m_ubo_matrices_handle == 99) {

		Print::print("Allocating Projection View Uniform Memory");
		
		// Activate buffer
		glGenBuffers(1, &m_ubo_matrices_handle);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_matrices_handle);

		// Allocate memory
		// 2 Mat4 matrices (16*4) * 2; Vec3 uses Vec4 alignment
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);

		// Unbind
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Link range of buffer (in this case its the entire buffer) to binding
		// point 0 (same as shaders using these using these uniforms)
		// The 'link' function must use the same binding point
		// ** Binding Point 0 **
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo_matrices_handle, 0, 2 * sizeof(glm::mat4));
		
	}
}

void OpenGL::OpenGLUniformBlock::set_projection_view_block_matrix_values(Camera& camera) const{

	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_matrices_handle);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(ProjectionMatrix::get_projection_matrix()));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera.get_view_matrix()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
}

void OpenGL::OpenGLUniformBlock::link_camera_position_block_to_shader(IShaderProgram& shader_program) {

	create_camera_position_block();
	IShaderUniformBlock::check_camera_position_block_created();
	Print::print("Linking shader program handle: '" + std::to_string(shader_program.get_handle()) + "' to uniform camera position block");

	// Uniform block index name is defined in GLSL shader code
	const unsigned int uniform_block_index = glGetUniformBlockIndex(shader_program.get_handle(), "uniform_camera_world_position");

	// ** Binding Point 1 **
	glUniformBlockBinding(shader_program.get_handle(), uniform_block_index, 1);

}

void OpenGL::OpenGLUniformBlock::create_camera_position_block(){

	if(m_ubo_camera_handle == 99){

		Print::print("Allocating Camera Position Uniform Memory");
		
		// Activate buffer
		glGenBuffers(1, &m_ubo_camera_handle);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_camera_handle);

		// Allocate memory
		// Vec3 uses Vec4 alignment
		glBufferData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);

		// Unbind
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// ** Binding Point 1 **
		glBindBufferRange(GL_UNIFORM_BUFFER, 1, m_ubo_camera_handle, 0, 1 * sizeof(glm::vec4));
	}
	
}

void OpenGL::OpenGLUniformBlock::set_camera_position_block_vector_values(Camera& camera) const{

	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_camera_handle);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(camera.get_camera_position()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
}

void OpenGL::OpenGLUniformBlock::update(Camera& camera) const{
	set_projection_view_block_matrix_values(camera);
	set_camera_position_block_vector_values(camera);
}

void OpenGL::OpenGLUniformBlock::destroy() const{
	Print::print("Destroying Matrix Uniform Buffer");
	glDeleteBuffers(1, &m_ubo_matrices_handle);
	glDeleteBuffers(1, &m_ubo_camera_handle);
}
