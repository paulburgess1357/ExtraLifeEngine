#pragma once
#include "entt/entity/registry.hpp"

namespace Transform{

	class WorldMovement{
		
	public:
		static void update(entt::registry& registry);
		static void reset_model_matrix(entt::registry& registry);
		
	};
	
} // namespace Transform

