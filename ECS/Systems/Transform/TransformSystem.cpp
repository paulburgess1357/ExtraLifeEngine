#include "TransformSystem.h"
#include "ModelMatrixReset.h"
#include "WorldMovement.h"
#include "WorldScale.h"
#include "WorldRotation.h"
#include "WorldOrbit.h"

void Transform::TransformSystem::update(entt::registry& registry){
	Transform::ModelMatrixReset::update(registry);
	Transform::WorldScale::update(registry);
	Transform::WorldMovement::update(registry);
	Transform::WorldRotation::update(registry);
	Transform::WorldOrbit::update(registry);
}
