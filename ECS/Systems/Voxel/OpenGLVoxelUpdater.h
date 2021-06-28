#pragma once
#include "IVoxelUpdater.h"

namespace OpenGL {

	class OpenGLVoxelUpdater : public IVoxelUpdater {
		void update() const override;		
	};

} // namespace OpenGL
