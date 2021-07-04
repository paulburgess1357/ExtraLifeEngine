#include "OpenGLModelRenderer.h"
#include "../../Matrix/MatrixFunctions.h"
#include "../../ECS/Components/Model/ModelComponent.h"
#include "../../../Components/Shader/ShaderComponent.h"
#include "../../../Components/Transform/TransformComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLModelRenderer::render(entt::registry& registry) const{
	
	registry.view<ModelComponent, TransformComponent, ShaderComponent>().each([](auto& model, auto& transform, auto& shader) {		
		
		shader.m_shader_program.set_uniform("model_matrix", transform.m_model_matrix);
		shader.m_shader_program.set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix));

		shader.m_shader_program.bind();

		for(const auto& mesh : model.m_model->get_mesh_vector()){

			const std::shared_ptr<ITextureHandler> mesh_texture_hander = mesh->get_texture_handler();
			mesh_texture_hander->bind_textures();

			glBindVertexArray(mesh->get_vao());
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->get_indices_size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			mesh_texture_hander->unbind_textures();
			
		}

		shader.m_shader_program.unbind();

	});
	
}
