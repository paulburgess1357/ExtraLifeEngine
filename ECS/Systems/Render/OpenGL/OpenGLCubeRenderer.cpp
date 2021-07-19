#include "OpenGLCubeRenderer.h"
#include "../../Matrix/MatrixFunctions.h"
#include "../../Matrix/ProjectionMatrix.h"
#include "../../ECS/Components/Shader/ShaderComponent.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include "../../Tests/GraphicsTesting/Cube/CubeComponent.h"
#include "../../Tests/GraphicsTesting/Cube/TexturedCubeComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLCubeRenderer::render(entt::registry& registry, Camera& camera) const{
	render_cube(registry, camera);
	render_textured_cube(registry, camera);
}

void OpenGL::OpenGLCubeRenderer::render_cube(entt::registry& registry, Camera& camera){
	
	registry.view<ShaderComponent, CubeComponent, TransformComponent>().each([&](auto& shader, auto& cube, auto& transform) {

		shader.m_shader_program->bind();
		
		shader.m_shader_program->set_uniform("model_matrix", transform.m_model_matrix, false);
		shader.m_shader_program->set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix, camera.get_view_matrix()), false);
		
		glBindVertexArray(cube.m_vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		shader.m_shader_program->unbind();

	});
}

void OpenGL::OpenGLCubeRenderer::render_textured_cube(entt::registry& registry, Camera& camera){
	
	registry.view<ShaderComponent, TexturedCubeComponent, TransformComponent>().each([&](auto& shader, auto& cube, auto& transform) {

		shader.m_shader_program->bind();
		
		shader.m_shader_program->set_uniform("model_matrix", transform.m_model_matrix, false);
		shader.m_shader_program->set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix, camera.get_view_matrix()), false);
		
		shader.m_shader_program->bind_textures_fast();
		
		glBindVertexArray(cube.m_vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		shader.m_shader_program->unbind_textures();
		shader.m_shader_program->unbind();

	});
}
