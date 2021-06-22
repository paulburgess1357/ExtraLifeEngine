#pragma once
#include "IVoxelUpdater.h"
#include "entt/entity/registry.hpp"

namespace OpenGL {

	class OpenGLVoxelUpdater : public IVoxelUpdater {
		void update() const override;		
	};

} // namespace OpenGL
