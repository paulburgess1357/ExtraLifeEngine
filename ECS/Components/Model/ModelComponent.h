#pragma once
#include "../../Model/Model/IModel.h"

struct ModelComponent{

	ModelComponent(IModel* model)
		:m_model{ model }{		
	}
	
	IModel* m_model = nullptr;
	
};
