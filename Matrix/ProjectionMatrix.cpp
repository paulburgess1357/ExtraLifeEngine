#include "ProjectionMatrix.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"
#include "../Environment/Interfaces/Window/IWindow.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

int ProjectionMatrix::m_window_width = 0;
int ProjectionMatrix::m_window_height = 0;
bool ProjectionMatrix::m_is_resizeable = true;
glm::mat4 ProjectionMatrix::m_projection_matrix = glm::mat4{ 1.0f };

const float ProjectionMatrix::DEFAULT_FOV{ 45.0f };
const float ProjectionMatrix::DEFAULT_ZNEAR{ 0.1f };
const float ProjectionMatrix::DEFAULT_ZFAR{ 300.0f };

std::shared_ptr<IWindow> ProjectionMatrix::m_window_ptr = nullptr;

void ProjectionMatrix::initialize_projection_matrix(const std::shared_ptr<IWindow>& window_ptr){
	if(window_ptr == nullptr){
		FatalError::fatal_error("IWindow pointer is null!  The projection matrix must be initialized with a non-null window pointer!");
	}
	
	m_window_ptr = window_ptr;
	set_projection_matrix();
}

void ProjectionMatrix::set_projection_matrix() {

	m_window_width = m_window_ptr->get_width();
	m_window_height = m_window_ptr->get_height();

	Print::print("IWindow: " + std::to_string(m_window_width) + "x" + std::to_string(m_window_height));

	m_projection_matrix = glm::perspective(glm::radians(DEFAULT_FOV),
		static_cast<float>(m_window_width) /
		static_cast<float>(m_window_height),
		DEFAULT_ZNEAR,
		DEFAULT_ZFAR);
}

glm::mat4 ProjectionMatrix::get_projection_matrix() {
	if (m_window_ptr->is_resizeable()) {
		if (m_window_ptr->get_width() != m_window_width || m_window_ptr->get_height() != m_window_height) {
			set_projection_matrix();
		}
	}
	return m_projection_matrix;
}