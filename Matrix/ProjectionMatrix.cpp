#include "ProjectionMatrix.h"
#include "../Utility/Print.h"
#include "../Environment/Interfaces/Window/IWindow.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

ProjectionMatrix::ProjectionMatrix(IWindow& window)
	:m_window_width{ 0 },
	m_window_height{ 0 },
	m_projection_matrix{ glm::mat4{ 1.0f } },
    DEFAULT_FOV{ 60.0f },
	DEFAULT_ZNEAR{ 0.1f },
	DEFAULT_ZFAR{ 2000.0f },
	m_window{ window }{
	set_projection_matrix();
}

void ProjectionMatrix::set_projection_matrix() {

	m_window_width = m_window.get_width();
	m_window_height = m_window.get_height();

	Print::print("IWindow: " + std::to_string(m_window_width) + "x" + std::to_string(m_window_height));

	m_projection_matrix = glm::perspective(glm::radians(DEFAULT_FOV),
		static_cast<float>(m_window_width) /
		static_cast<float>(m_window_height),
		DEFAULT_ZNEAR,
		DEFAULT_ZFAR);
}

glm::mat4 ProjectionMatrix::get_projection_matrix() {
	if (m_window.is_resizeable()) {
		if (m_window.get_width() != m_window_width || m_window.get_height() != m_window_height) {
			set_projection_matrix();
		}
	}
	return m_projection_matrix;
}
