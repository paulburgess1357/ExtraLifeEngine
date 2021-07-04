#pragma once
#include "../Interfaces/IVoxelRenderer.h"
#include "../OpenGL/OpenGLVoxelRenderer.h"

namespace OpenGL{

	class OpenGLVoxelRenderer : public IVoxelRenderer {
	public:
		OpenGLVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram& shader_program);
		void render() const override;
	};
	
} // namespace OpenGL