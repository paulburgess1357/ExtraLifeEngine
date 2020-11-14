#include "WorldScale.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include "../../ECS/Components/Transform/ScaleComponent.h"
#include <glm/gtc/matrix_transform.hpp>

void Transform::WorldScale::update(entt::registry& registry){
	registry.view<TransformComponent, ScaleComponent>().each([](auto& transform, auto& scale_val) {
		if (scale_val.m_scale != 1.0f) {
			transform.m_model_matrix = glm::scale(transform.m_model_matrix, glm::vec3(scale_val.m_scale));
		}
	});
}
