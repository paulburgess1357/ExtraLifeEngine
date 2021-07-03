#pragma once
#include <memory>
#include "../../../ResourceManagement/VoxelResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"

class IVoxelUpdater {

public:
	IVoxelUpdater(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range_updater);
	virtual ~IVoxelUpdater() = default;
	virtual void update() const = 0;
	static std::unique_ptr<IVoxelUpdater> get_voxel_updater(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range_updater);

protected:
	const VoxelResource& m_voxel_resource;
	const WorldPositionsInRangeUpdater& m_world_positions_in_range_updater;
};
