#include "OpenGLCubeRenderer.h"
#include "../../ECS/Components/Shader/ShaderComponent.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include "../../Matrix/ProjectionMatrix.h"
#include "../../Tests/GraphicsTesting/Cube/CubeComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLCubeRenderer::render(entt::registry& registry, Camera& camera) const{

	registry.view<ShaderComponent, CubeComponent, TransformComponent>().each([](auto& shader, auto& cube, auto& transform) {

		shader.m_shader_program->set_uniform("model", transform.m_model_matrix);

		shader.m_shader_program->bind();
		glBindVertexArray(cube.m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		shader.m_shader_program->unbind();

	});
	
}

