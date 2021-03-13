#pragma once
#include <entt/entity/registry.hpp>

namespace Voxel{
	
	class VoxelSystem {
	public:
		static void update(entt::registry& registry);
	};
	
} // namespace Voxel
