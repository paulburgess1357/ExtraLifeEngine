#pragma once
#include "../../../../Camera/Camera.h"
#include "entt/entity/registry.hpp"
#include <memory>

class IVoxelRenderer{
	
public:
	virtual ~IVoxelRenderer() = default;
	virtual void render(entt::registry& registry, Camera& camera) const = 0;
	static std::shared_ptr<IVoxelRenderer> get_voxel_renderer();
};

