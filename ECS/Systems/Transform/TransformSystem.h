#pragma once
#include "entt/entity/registry.hpp"

namespace Transform{

	class TransformSystem {
	public:
		static void update(entt::registry& registry);
	};
	
} // namespace Transform


