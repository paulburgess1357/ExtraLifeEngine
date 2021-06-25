#pragma once
#include "ICommand.h"
#include "../../Interface/ImGuiInterface.h"

class ImGuiDisplayCommand : public ICommand{

public:
	ImGuiDisplayCommand() = default;
	void execute() override{
		ImGuiNS::ImGuiInterface::toggle_interface();
	}
	
};