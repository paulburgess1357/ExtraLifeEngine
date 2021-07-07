#include "TransformSystem.h"
#include "ModelMatrixReset.h"
#include "WorldMovement.h"
#include "WorldScale.h"
#include "WorldRotation.h"
#include "WorldOrbit.h"

void Transform::TransformSystem::update(entt::registry& registry){
	ModelMatrixReset::update(registry);
	WorldScale::update(registry);
	WorldMovement::update(registry);
	WorldRotation::update(registry);
	WorldOrbit::update(registry);
}
