#pragma once
#include <glm/glm.hpp>

struct DirectionalLight{
	glm::vec3 direction { 0.0f, 1.0f, 0.0f };
};

// Direction: Direction light is coming from (so (0, 1, 0) is coming FROM above and pointing downwards)
// Ambient: E.g. Moonlight
// Diffuse: The directional impact of the light.  The more an object faces the 
//          light, the brighter it becomes
// Specular: The bright spot of light that appears on shiny objects.  The color
//           highlight is typically closer to the color of the light
