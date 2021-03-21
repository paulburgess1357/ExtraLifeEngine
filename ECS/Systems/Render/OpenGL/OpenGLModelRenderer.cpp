#include "OpenGLModelRenderer.h"
#include "../../Matrix/MatrixFunctions.h"
#include "../../ECS/Components/Model/ModelComponent.h"
#include "../../../Components/Shader/ShaderComponent.h"
#include "../../../Components/Transform/TransformComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLModelRenderer::render(entt::registry& registry) const{
	
	registry.view<ModelComponent, TransformComponent, ShaderComponent>().each([](auto& model, auto& transform, auto& shader) {		
		
		shader.m_shader_program->set_uniform("model_matrix", transform.m_model_matrix);
		shader.m_shader_program->set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix));

		shader.m_shader_program->bind();

		for(const auto& mesh : model.m_model->get_mesh_vector()){
			//mesh->draw();

			mesh->m_texture_handler->bind_textures();

			glBindVertexArray(mesh->get_vao());
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->get_indices_size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			mesh->m_texture_handler->unbind_textures();
			
		}

		shader.m_shader_program->unbind();

	});

	//auto view = registry.view<ModelComponent, TransformComponent, ShaderComponent>();

	//for (auto entity : view) {

	//	auto& model = view.get<ModelComponent>(entity);
	//	auto& transform = view.get<TransformComponent>(entity);
	//	auto& shader = view.get<ShaderComponent>(entity);

	//	shader.m_shader_program->set_uniform("model_matrix", transform.m_model_matrix);
	//	shader.m_shader_program->set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix));

	//	shader.m_shader_program->bind();

	//	for (const auto& mesh : model.m_model->get_mesh_vector()) {
	//		//mesh->draw();

	//		mesh->m_texture_handler->bind_textures();

	//		glBindVertexArray(mesh->get_vao());
	//		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->get_indices_size()), GL_UNSIGNED_INT, 0);
	//		glBindVertexArray(0);

	//		mesh->m_texture_handler->unbind_textures();

	//	}

	//	shader.m_shader_program->unbind();

	//}

	
}
