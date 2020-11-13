#pragma once
#include "ICommand.h"

class NullCommand : public ICommand{
public:
	void execute() override{
		
	}
};
