#include "InterfaceCameraData.h"
#include "../ExternalResources/imgui/imgui_impl_opengl3.h"
#include <glm/glm.hpp>

ImGuiNS::InterfaceCameraData::InterfaceCameraData(Camera& camera)
	:m_camera_data(camera),
	 m_camera_speed(0.05){	
}

void ImGuiNS::InterfaceCameraData::display() const{
	const glm::vec3 camera_coords = m_camera_data.get_camera_position();	
	ImGui::Text("Camera Coordinates: %.2f, %.2f, %.2f", camera_coords.x, camera_coords.y, camera_coords.z);
}

void ImGuiNS::InterfaceCameraData::update_camera_speed() {
	ImGui::SliderFloat("Camera Speed", &m_camera_speed, 0.01f, 0.50f);
	m_camera_data.set_camera_speed(m_camera_speed);
}
