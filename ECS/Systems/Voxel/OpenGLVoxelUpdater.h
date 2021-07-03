#pragma once
#include "IVoxelUpdater.h"

namespace OpenGL {

	class OpenGLVoxelUpdater : public IVoxelUpdater {
	public:
		OpenGLVoxelUpdater(VoxelResource& voxel_resource);
		void update() const override;		
	};

} // namespace OpenGL
