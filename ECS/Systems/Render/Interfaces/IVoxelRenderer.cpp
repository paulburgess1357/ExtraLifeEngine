#include "IVoxelRenderer.h"
#include "../OpenGL/OpenGLVoxelRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

IVoxelRenderer::IVoxelRenderer(VoxelResource& voxel_resource)
	:m_voxel_resource(voxel_resource){	
}


std::unique_ptr<IVoxelRenderer> IVoxelRenderer::get_voxel_renderer(VoxelResource& voxel_resource) {
	
	std::unique_ptr<IVoxelRenderer> renderer { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		renderer = std::make_unique<OpenGL::OpenGLVoxelRenderer>(voxel_resource);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan voxel renderer does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel renderer.");
	}

	return renderer;	
}

