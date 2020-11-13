#include "WorldMovement.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include "../../ECS/Components/Transform/MovementVelocityComponent.h"
#include <glm/gtc/matrix_transform.hpp>

void Transform::WorldMovement::reset_model_matrix(entt::registry& registry){
	registry.view<TransformComponent>().each([](auto& transform) {
		transform.m_model_matrix = glm::translate(glm::mat4(1.0f), transform.m_world_position); 
	});
}

void Transform::WorldMovement::update(entt::registry& registry){
	registry.view<TransformComponent, MovementVelocityComponent>().each([](auto& transform, auto& movement_velocity) {				
		transform.m_world_position += movement_velocity.m_movement_velocity;
		transform.m_model_matrix = glm::translate(transform.m_model_matrix, transform.m_world_position);
	});
}
