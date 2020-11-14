#pragma once
#include "../../Components/Transform/OrbitComponent.h"
#include "entt/entity/registry.hpp"

namespace Transform{

	class WorldOrbit {
	public:
		static void update(entt::registry& registry);
	private:
		static glm::mat4 orbit(OrbitComponent& orbit);
		static glm::quat apply_counter_rotation(OrbitComponent& orbit);
		static void clamp_orbit_orientation(float& orientation_value);

	};
	
} // namespace Transform


