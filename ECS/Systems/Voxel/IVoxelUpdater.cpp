#include "IVoxelUpdater.h"
#include "OpenGLVoxelUpdater.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../Utility/FatalError.h"

IVoxelUpdater::IVoxelUpdater(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range_updater)
	:m_voxel_resource(voxel_resource),
	m_world_positions_in_range_updater{ world_positions_in_range_updater  }{
}

std::unique_ptr<IVoxelUpdater> IVoxelUpdater::get_voxel_updater(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range_updater){

	std::unique_ptr<IVoxelUpdater> updater { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		updater = std::make_unique<OpenGL::OpenGLVoxelUpdater>(voxel_resource, world_positions_in_range_updater);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {		
		FatalError::fatal_error("Vulkan voxel updater does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel updater.");
	}
	
	return updater;
	
}
