#pragma once
#include "../Interfaces/IModelRenderer.h"

namespace OpenGL{

	class OpenGLModelRenderer : public IModelRenderer {
	public:
		void render(entt::registry& registry, Camera& camera) const override;
	};
	
} // namespace OpenGL


