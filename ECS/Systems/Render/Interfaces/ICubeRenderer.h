#pragma once
#include "entt/entity/registry.hpp"
#include "../../../../Camera/Camera.h"
#include <memory>

class ICubeRenderer{
public:
	virtual ~ICubeRenderer() = default;
	virtual void render(entt::registry& registry, Camera& camera) const = 0;
	static std::unique_ptr<ICubeRenderer> get_cube_renderer();	
};
