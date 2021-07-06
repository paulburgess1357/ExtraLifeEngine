#pragma once
#include "../Camera/Camera.h"

namespace ImGuiNS {
	
	class  InterfaceCameraData {

	public:
		InterfaceCameraData(Camera& camera);
		void display() const;
		void update_camera_speed();

	private:
		Camera& m_camera_data;
		float m_camera_speed;
	};
	
} // namespace ImGuiNS