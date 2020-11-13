#pragma once
#include "ICommand.h"
#include "../Processing/MouseManager.h"
#include "../../Utility/Print.h"
#include <glm/glm.hpp>
#include <string>

class MouseCommandTest : public ICommand {
	
public:
	void execute() override{
		Print::print("Mouse button pressed!");
		const glm::vec2 coords = MouseManager::get_coords();
		Print::print(std::to_string(coords.x) + "," + std::to_string(coords.y));
	}
	
};

