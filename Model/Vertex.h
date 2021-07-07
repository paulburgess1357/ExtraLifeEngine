#pragma once
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 m_position{ 0.0f };
	glm::vec3 m_normals{ 0.0f };
	glm::vec2 m_tex_coords { 0.0f };

	glm::vec3 m_tangent{ 0.0f };
	glm::vec3 m_bitangent{ 0.0f };	
};
