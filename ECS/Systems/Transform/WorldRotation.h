#pragma once
#include "../../Components/Transform/RotationComponent.h"
#include "entt/entity/registry.hpp"
#include <glm/gtx/quaternion.hpp>

namespace Transform{

	class WorldRotation {

	public:
		static void update(entt::registry& registry);
		
	private:
		static glm::quat pitch(RotationComponent& rotation);
		static glm::quat yaw(RotationComponent& rotation);
		static glm::quat roll(RotationComponent& rotation);
		static glm::quat rotate_custom_axis(RotationComponent& rotation);
		static void clamp_rotation_orientation(float& orientation_value);
		
		static const glm::vec3 DEFAULT_ROTATION_X;
		static const glm::vec3 DEFAULT_ROTATION_Y;
		static const glm::vec3 DEFAULT_ROTATION_Z;

	};
	
} // namespace Transform


