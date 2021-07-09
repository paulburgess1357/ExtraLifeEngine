#include "OpenGLCubeMapRenderer.h"
#include "../../ECS/Components/Shader/ShaderComponent.h"
#include "../../ECS/Components/CubeMap/CubeMapComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLCubeMapRenderer::render(entt::registry& registry, Camera& camera) const{

	auto view = registry.view<ShaderComponent, CubeMapComponent>();
	
	for (auto entity : view){		

		auto& shader = view.get<ShaderComponent>(entity);
		auto& cubemap = view.get<CubeMapComponent>(entity);

		shader.m_shader_program->bind();
		shader.m_shader_program->set_uniform("view_matrix_no_translation", glm::mat4(glm::mat3(camera.get_view_matrix())), false);
				
		shader.m_shader_program->bind_textures_fast();

		glBindVertexArray(cubemap.m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		
		shader.m_shader_program->unbind_textures();
		shader.m_shader_program->unbind();		
	}
	
}
