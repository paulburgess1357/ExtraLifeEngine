#pragma once
#include "../Environment/Interfaces/Window/IWindow.h"
#include <glm/glm.hpp>

class ProjectionMatrix{

public:
	ProjectionMatrix(IWindow& window);	
	glm::mat4 get_projection_matrix();
	
private:
	void set_projection_matrix();
	
	int m_window_width;
	int m_window_height;
	glm::mat4 m_projection_matrix;

	const float DEFAULT_FOV;
	const float DEFAULT_ZNEAR;
	const float DEFAULT_ZFAR;

	IWindow& m_window;
	
};
