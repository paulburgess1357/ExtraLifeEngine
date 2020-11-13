#pragma once
#include "../../../../Camera/Camera.h"
#include "../Interfaces/ICubeRenderer.h"

namespace OpenGL {

	class OpenGLCubeRenderer : public ICubeRenderer {
		void render(entt::registry& registry, Camera& camera) const override;
	};
	
} // namespace Systems::Render::OpenGL



