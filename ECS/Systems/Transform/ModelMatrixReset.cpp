#include "ModelMatrixReset.h"
#include "WorldMovement.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

void Transform::ModelMatrixReset::update(entt::registry& registry) {
	registry.view<TransformComponent>().each([](auto& transform) {
		transform.m_model_matrix = glm::translate(glm::mat4(1.0f), transform.m_world_position);
	});
}
