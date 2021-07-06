#pragma once
#include "ICommand.h"
#include "../../Environment/Interfaces/Window/IWindow.h"
#include "../Processing/MouseHandler.h"

class MouseControlCommmand : public ICommand{

public:
	MouseControlCommmand(IWindow& window, MouseHandler& mouse_handler)
		:m_window{ window },
		 m_mouse_handler{ mouse_handler }{
	}
	
	void execute() override{
		m_window.toggle_mouse();
		m_mouse_handler.set_mouse_enabled(m_window.get_mouse_enabled());
	}
private:
	IWindow& m_window;
	MouseHandler& m_mouse_handler;
	
};
