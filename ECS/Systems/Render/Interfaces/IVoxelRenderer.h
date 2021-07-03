#pragma once
#include "../../ResourceManagement/VoxelResource.h"
#include "entt/entity/registry.hpp"
#include <memory>

class IVoxelRenderer{
	
public:
	IVoxelRenderer();
	virtual ~IVoxelRenderer() = default;
	virtual void render() const = 0;
	static std::unique_ptr<IVoxelRenderer> get_voxel_renderer(VoxelResource* m_voxel_resource);
};