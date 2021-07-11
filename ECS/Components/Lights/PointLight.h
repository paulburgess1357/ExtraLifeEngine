#pragma once
#include "ILight.h"
#include <glm/glm.hpp>

// PointLight Definition: A light source that illuminates in all directions,
//                        where the intensity decreases over distance.
//                        E.g. Lightbulb or a torch

struct PointLight : ILight{

	PointLight(std::string light_name)
		:ILight{ std::move(light_name) }{		
	}
	PointLight(std::string light_name, const glm::vec3& position, const float constant, const float linear, const float quadratic)
		:ILight{ std::move(light_name) },
		 m_position{ position },
		 m_constant{ constant },
		 m_linear{ linear },
		 m_quadratic{ quadratic }{		
	}
	
	glm::vec3 m_position { 0.0f, 4.0f, 0.0f };

	// Attenuation
	//float m_constant { 1.0f };
	//float m_linear { 0.45f };
	//float m_quadratic { 0.0075f };

	float m_constant{ 1.0f };
	float m_linear{ 0.09f };
	float m_quadratic{ 0.032f };

};

// m_position: Position of the light source (currently using world coordinates)
// float m_constant: Typically left a 1.0
// float m_linear: Reduces light intenstiy in a linear fashion                  
// float m_quadratic: Reduces lght intensity in a quadratic fashion

// Ogre3D Wiki Lighting Table
//Distance	Constant	Linear	Quadratic
//	7	     1.0	     0.7	   1.8
//	13	     1.0	     0.35	   0.44
//	20	     1.0		 0.22	   0.20
//	32	     1.0		 0.14	   0.07
//	50	     1.0		 0.09	   0.032
//	65	     1.0		 0.07	   0.017
//	100		 1.0	     0.045	   0.0075
//	160		 1.0	     0.027	   0.0028
//	200		 1.0		 0.022	   0.0019
//	325		 1.0		 0.014	   0.0007
//	600		 1.0		 0.007	   0.0002
//	3250	 1.0		 0.0014	   0.000007