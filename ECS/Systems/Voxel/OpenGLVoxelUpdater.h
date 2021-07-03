#pragma once
#include "IVoxelUpdater.h"

namespace OpenGL {

	class OpenGLVoxelUpdater : public IVoxelUpdater {
	public:
		OpenGLVoxelUpdater(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range_updater);
		void update() const override;		
	};

} // namespace OpenGL
