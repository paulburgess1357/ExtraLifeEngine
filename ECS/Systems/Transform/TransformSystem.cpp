#include "TransformSystem.h"
#include "WorldMovement.h"

void Transform::TransformSystem::update(entt::registry& registry){
	Transform::WorldMovement::reset_model_matrix(registry);
	Transform::WorldMovement::update(registry);
}
