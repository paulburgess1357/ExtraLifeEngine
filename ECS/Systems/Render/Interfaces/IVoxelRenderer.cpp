#include "IVoxelRenderer.h"
#include "../OpenGL/OpenGLVoxelRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"
#include "../../../../Utility/Print.h"

IVoxelRenderer::IVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram* shader_program)
	:m_voxel_resource{ voxel_resource },
	m_world_positions_in_range_updater{ world_positions_in_range },
	m_voxel_shader_program{ shader_program }{
}

std::unique_ptr<IVoxelRenderer> IVoxelRenderer::get_voxel_renderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, ShaderResource& shader_resource, const VoxelMetaData& voxel_meta_data) {
	
	std::unique_ptr<IVoxelRenderer> renderer { nullptr };
	
	// Special use case where we don't want the fatal error from accessing a
	// shader that doesn't exist!  If the voxel shader is a nullptr, it means	
	// it means we aren't running in voxel mode.  As such, the voxel renderer
	// will not run anything.
	IShaderProgram* shader_program = shader_resource.get(voxel_meta_data.m_voxel_shader, true);
	run_shader_ptr_checks(world_positions_in_range, shader_program);

	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		renderer = std::make_unique<OpenGL::OpenGLVoxelRenderer>(voxel_resource, world_positions_in_range, shader_program);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan voxel renderer does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel renderer.");
	}

	return renderer;	
}

void IVoxelRenderer::run_shader_ptr_checks(const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram* shader_program) {
	if (!world_positions_in_range.get_all_world_positions_in_camera_range().empty() && shader_program == nullptr) {
		FatalError::fatal_error("You have world positions in range for voxel creation, but your voxel shader is a nullptr");
	}

	if (shader_program == nullptr) {
		Print::print("\n****Voxel Shader Check: nullptr****\n");
	}
}

