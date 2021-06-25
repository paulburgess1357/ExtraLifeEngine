#include "InterfaceCameraData.h"
#include "../ExternalResources/imgui/imgui_impl_opengl3.h"
#include <glm/glm.hpp>

ImGuiNS::InterfaceCameraData::InterfaceCameraData(const Camera& camera)
	:m_camera_data(camera){	
}

void ImGuiNS::InterfaceCameraData::display() const{
	const glm::vec3 camera_coords = m_camera_data.get_camera_position();
	ImGui::Text("Camera Coordinates: %.2f, %.2f, %.2f", camera_coords.x, camera_coords.y, camera_coords.z);
}