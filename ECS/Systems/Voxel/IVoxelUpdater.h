#pragma once
#include "entt/entity/registry.hpp"

class IVoxelUpdater {

public:
	virtual ~IVoxelUpdater() = default;
	virtual void update(entt::registry& registry) const = 0;
	static std::shared_ptr<IVoxelUpdater> get_voxel_updater();
};