#pragma once
#include <string>

class ILight {
public:
	explicit ILight(std::string light_name)
		:m_light_name{ std::move(light_name) }{		
	}	
	std::string m_light_name = "No light name assigned";
};

// Direction: Direction light is coming from (so (0, 1, 0) is coming FROM above and pointing downwards)
// Ambient: E.g. Moonlight
// Diffuse: The directional impact of the light.  The more an object faces the 
//          light, the brighter it becomes
// Specular: The bright spot of light that appears on shiny objects.  The color
//           highlight is typically closer to the color of the light