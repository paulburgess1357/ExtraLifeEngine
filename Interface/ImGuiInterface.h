#pragma once
#include "InterfaceCameraData.h"
#include "../Camera/Camera.h"
#include "../Environment/Interfaces/Window/IWindow.h"
#include <memory>

namespace ImGuiNS {
	
	class ImGuiInterface {

	public:
		static void initialize_window(std::shared_ptr<IWindow>& window);
		static void initialize_camera_data(const Camera& camera);
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
		static void check_camera_interface();

		static std::shared_ptr<InterfaceCameraData> m_interface_camera_data;
		static bool m_display_interface;
	};
	
} // namespace ImGuiNS


