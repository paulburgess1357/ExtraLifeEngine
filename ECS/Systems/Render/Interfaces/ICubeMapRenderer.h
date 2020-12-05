#pragma once
#include "../../../../Camera/Camera.h"
#include "entt/entity/registry.hpp"
#include <memory>

class ICubeMapRenderer{
	
public:
	virtual ~ICubeMapRenderer() = default;
	virtual void render(entt::registry& registry, Camera& camera) const = 0;
	static std::shared_ptr<ICubeMapRenderer> get_cube_renderer();
};

