#include "OpenGLCubeRenderer.h"
#include "../../ECS/Components/Shader/ShaderComponent.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include "../../Matrix/ProjectionMatrix.h"
#include "../../Tests/GraphicsTesting/Cube/CubeComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLCubeRenderer::render(entt::registry& registry, Camera& camera) const{

	// TODO: view and projection matrices are global
	// TODO: make this the 'each' version once I set those globally
	
	auto view = registry.view<ShaderComponent, CubeComponent, TransformComponent>();
	
	for(auto entity : view){

		auto& shader = view.get<ShaderComponent>(entity);
		auto& cube = view.get<CubeComponent>(entity);
		auto& transform = view.get<TransformComponent>(entity);

		shader.m_shader_program->set_uniform("model", transform.m_model_matrix);
		shader.m_shader_program->set_uniform("view", camera.get_view_matrix()); // can be set as global
		shader.m_shader_program->set_uniform("projection", ProjectionMatrix::get_projection_matrix());	// can be set as global	
				
		shader.m_shader_program->bind();
		glBindVertexArray(cube.m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		shader.m_shader_program->unbind();
		
	}
}

