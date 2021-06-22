#pragma once
#include "entt/entity/registry.hpp"
#include <memory>

class IVoxelRenderer{
	
public:
	virtual ~IVoxelRenderer() = default;
	virtual void render() const = 0;
	static std::shared_ptr<IVoxelRenderer> get_voxel_renderer();
};