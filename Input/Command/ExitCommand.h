#pragma once
#include "ICommand.h"
#include "../../Game/GameManager.h"
	
class ExitCommand : public ICommand {
	
public:
	ExitCommand(GameManager& game_manager)
		:m_game_manager{ game_manager } {
	}
	void execute() override{
		m_game_manager.set_game_state(GameState::EXIT);
	}
	
private:
	GameManager& m_game_manager;
	
};
