#pragma once
#include "../../../../Camera/Camera.h"
#include "../Interfaces/ICubeRenderer.h"

namespace OpenGL {

	class OpenGLCubeRenderer : public ICubeRenderer {		
		void render(entt::registry& registry, Camera& camera) const override;
		static void render_cube(entt::registry& registry, Camera& camera);
		static void render_textured_cube(entt::registry& registry, Camera& camera);
	};
	
} // namespace Systems::Render::OpenGL



