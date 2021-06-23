#pragma once
#include "ICommand.h"
#include "../../Environment/Interfaces/Window/IWindow.h"
#include <memory>

class MouseControlCommmand : public ICommand{

public:
	MouseControlCommmand(std::shared_ptr<IWindow>& window)
		:m_window{ window }{		
	}
	
	void execute() override{
		if(mouse_enabled){
			m_window->en
		} else{
			
		}		
	}
private:
	std::shared_ptr<IWindow> m_window;
	bool mouse_enabled = false;
	
};
