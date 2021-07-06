#pragma once
#include "InterfaceCameraData.h"
#include "../Camera/Camera.h"
#include "../Environment/Interfaces/Window/IWindow.h"
#include <memory>

namespace ImGuiNS {
	
	class ImGuiInterface {

	public:
		static void initialize_window(IWindow& window);
		static void initialize_camera_data(Camera& camera);
		static void update();
		static void render();
		static void destroy();

		static void toggle_interface();
		
	private:
		ImGuiInterface() = default;
		~ImGuiInterface() = default;
		static void debug_menu();
		static void fps();
		static void globals();

		static std::unique_ptr<InterfaceCameraData> m_interface_camera_data;
		static bool m_display_interface;
	};
	
} // namespace ImGuiNS


