#pragma once
#include <glm/glm.hpp>

struct Vertex {

	glm::vec3 m_position;
	glm::vec3 m_normals;
	glm::vec2 m_tex_coords;

	glm::vec3 m_tangent;
	glm::vec3 m_bitangent;
	
};