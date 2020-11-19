#pragma once
#include "../Environment/Interfaces/Window/IWindow.h"
#include <glm/glm.hpp>
#include <memory>

class ProjectionMatrix{

public:
	static void initialize_projection_matrix(const std::shared_ptr<IWindow>& window_ptr);
	static glm::mat4 get_projection_matrix();
private:
	ProjectionMatrix() = default;
	static void set_projection_matrix();
	
private:		
	static int m_window_width;
	static int m_window_height;
	static bool m_is_resizeable;
	static glm::mat4 m_projection_matrix;

	static const float DEFAULT_FOV;
	static const float DEFAULT_ZNEAR;
	static const float DEFAULT_ZFAR;

	static std::shared_ptr<IWindow> m_window_ptr;
	
};

