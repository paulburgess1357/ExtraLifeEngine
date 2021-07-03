#include "IVoxelRenderer.h"
#include "../OpenGL/OpenGLVoxelRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

IVoxelRenderer::IVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range)
	:m_voxel_resource{ voxel_resource },
	m_world_positions_in_range_updater{ world_positions_in_range }{
}


std::unique_ptr<IVoxelRenderer> IVoxelRenderer::get_voxel_renderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range) {
	
	std::unique_ptr<IVoxelRenderer> renderer { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		renderer = std::make_unique<OpenGL::OpenGLVoxelRenderer>(voxel_resource, world_positions_in_range);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan voxel renderer does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel renderer.");
	}

	return renderer;	
}

