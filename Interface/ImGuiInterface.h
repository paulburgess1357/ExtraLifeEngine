#pragma once
#include "../Environment/Interfaces/Window/IWindow.h"
#include <memory>

class ImGuiInterface {
public:

	static void initialize(std::shared_ptr<IWindow>& window);
	static void update();
	static void render();
	static void destroy();
private:
	ImGuiInterface() = default;
	~ImGuiInterface() = default;
	static void debug_menu();
	static void fps();
	static void globals();
};

