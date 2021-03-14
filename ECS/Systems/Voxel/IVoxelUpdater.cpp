#include "IVoxelUpdater.h"
#include "OpenGLVoxelUpdater.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../Utility/FatalError.h"

std::shared_ptr<IVoxelUpdater> IVoxelUpdater::get_voxel_updater(){
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLVoxelUpdater>();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<IVoxelUpdater> voxel_updater = nullptr;
		FatalError::fatal_error("Vulkan voxel updater does not exist!.");
		return voxel_updater;
	}

	FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel updater.");
	std::shared_ptr<IVoxelUpdater> voxel_updater = nullptr;
	return voxel_updater;
}
