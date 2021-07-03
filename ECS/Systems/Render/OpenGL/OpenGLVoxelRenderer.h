#pragma once
#include "../Interfaces/IVoxelRenderer.h"
#include "../OpenGL/OpenGLVoxelRenderer.h"

namespace OpenGL{

	class OpenGLVoxelRenderer : public IVoxelRenderer {
	public:
		OpenGLVoxelRenderer(VoxelResource& voxel_resource);
		void render() const override;
	};
	
} // namespace OpenGL