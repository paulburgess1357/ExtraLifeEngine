#include "IVoxelRenderer.h"
#include "../OpenGL/OpenGLVoxelRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

std::shared_ptr<IVoxelRenderer> IVoxelRenderer::get_voxel_renderer(){

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLVoxelRenderer>();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<IVoxelRenderer> voxel_renderer = nullptr;
		FatalError::fatal_error("Vulkan voxel renderer does not exist!.");
		return voxel_renderer;
	}

	FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel renderer.");
	std::shared_ptr<IVoxelRenderer> voxel_renderer = nullptr;
	return voxel_renderer;
	
}

