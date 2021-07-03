#pragma once
#include <memory>
#include "../../../ResourceManagement/VoxelResource.h"

class IVoxelUpdater {

public:
	IVoxelUpdater(VoxelResource& voxel_resource);
	virtual ~IVoxelUpdater() = default;
	virtual void update() const = 0;
	static std::unique_ptr<IVoxelUpdater> get_voxel_updater(VoxelResource& m_voxel_resource);

protected:
	VoxelResource& m_voxel_resource;
};
