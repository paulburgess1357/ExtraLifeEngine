#include "IVoxelUpdater.h"
#include "OpenGLVoxelUpdater.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../Utility/FatalError.h"

std::shared_ptr<IVoxelUpdater> IVoxelUpdater::get_voxel_updater(){

	std::shared_ptr<IVoxelUpdater> updater { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		updater = std::make_shared<OpenGL::OpenGLVoxelUpdater>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {		
		FatalError::fatal_error("Vulkan voxel updater does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel updater.");
	}
	
	return updater;
	
}
