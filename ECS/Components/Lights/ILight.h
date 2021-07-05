#pragma once
#include <string>

class ILight {
public:
	explicit ILight(std::string light_name)
		:m_light_name{ std::move(light_name) }{		
	}
	
	std::string m_light_name = "No light name assigned";
};
