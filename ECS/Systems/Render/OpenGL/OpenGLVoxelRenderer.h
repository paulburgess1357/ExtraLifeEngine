#pragma once
#include "../Interfaces/IVoxelRenderer.h"

namespace OpenGL{

	class OpenGLVoxelRenderer : public IVoxelRenderer {
	public:
		void render(entt::registry& registry, Camera& camera) const override;		
	};
	
} // namespace OpenGL