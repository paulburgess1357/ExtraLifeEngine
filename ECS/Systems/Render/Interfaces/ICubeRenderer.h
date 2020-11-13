#pragma once
#include "../../../../Camera/Camera.h"
#include "entt/entity/registry.hpp"

class ICubeRenderer{

public:
	virtual ~ICubeRenderer() = default;
	virtual void render(entt::registry& registry, Camera& camera) const = 0;
	
};
