#pragma once
#include <glm/glm.hpp>

// PointLight Definition: A light source that illuminates in all directions,
//                        where the intensity decreases over distance.
//                        E.g. Lightbulb or a torch

struct PointLight {

	glm::vec3 m_position { 0.0f, 4.0f, 0.0f };

	// Attenuation
	float m_constant { 1.0f };
	float m_linear{ 0.09f };
	float m_quadratic{ 0.032f };

};

// m_position: Position of the light source (currently using world coordinates)
// float m_constant: Typically left a 1.0
// float m_linear: Reduces light intenstiy in a linear fashion                  
// float m_quadratic: Reduces lght intensity in a quadratic fashion 