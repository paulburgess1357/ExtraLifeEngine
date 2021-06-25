#pragma once
#include "../Camera/Camera.h"

namespace ImGuiNS {
	
	class  InterfaceCameraData {

	public:
		InterfaceCameraData(const Camera& camera);
		void display() const;

	private:
		const Camera& m_camera_data;
	};
	
} // namespace ImGuiNS