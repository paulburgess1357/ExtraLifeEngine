#include "OpenGLModelRenderer.h"
#include "../../Matrix/MatrixFunctions.h"
#include "../../ECS/Components/Model/ModelComponent.h"
#include "../../../Components/Shader/ShaderComponent.h"
#include "../../../Components/Transform/TransformComponent.h"

void OpenGL::OpenGLModelRenderer::render(entt::registry& registry) const{
	
	registry.view<ModelComponent, TransformComponent, ShaderComponent>().each([](auto& model, auto& transform, auto& shader) {		
		
		shader.m_shader_program->set_uniform("model_matrix", transform.m_model_matrix);
		shader.m_shader_program->set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix));

		shader.m_shader_program->bind();
		
		model.m_model->draw();
		shader.m_shader_program->unbind();

	});
}
