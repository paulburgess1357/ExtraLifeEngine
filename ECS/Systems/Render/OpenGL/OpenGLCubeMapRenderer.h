#pragma once
#include "../../../../Camera/Camera.h"
#include "../Interfaces/ICubeMapRenderer.h"

namespace OpenGL{

	class OpenGLCubeMapRenderer : public ICubeMapRenderer {		
	public:
		void render(entt::registry& registry, Camera& camera) const override;		
	};
	
} // namespace OpenGL


