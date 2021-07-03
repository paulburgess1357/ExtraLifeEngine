#include "IVoxelUpdater.h"
#include "OpenGLVoxelUpdater.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../Utility/FatalError.h"

IVoxelUpdater::IVoxelUpdater(VoxelResource& voxel_resource)
	:m_voxel_resource(voxel_resource){
}


std::unique_ptr<IVoxelUpdater> IVoxelUpdater::get_voxel_updater(VoxelResource& m_voxel_resource){

	std::unique_ptr<IVoxelUpdater> updater { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		updater = std::make_unique<OpenGL::OpenGLVoxelUpdater>(m_voxel_resource);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {		
		FatalError::fatal_error("Vulkan voxel updater does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel updater.");
	}
	
	return updater;
	
}
