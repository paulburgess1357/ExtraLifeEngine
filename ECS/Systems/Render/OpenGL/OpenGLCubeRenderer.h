#pragma once
#include "../Interfaces/ICubeRenderer.h"

namespace OpenGL {

	class OpenGLCubeRenderer : public ICubeRenderer {		
		void render(entt::registry& registry) const override;
		static void render_cube(entt::registry& registry);
		static void render_textured_cube(entt::registry& registry);
	};
	
} // namespace OpenGL
