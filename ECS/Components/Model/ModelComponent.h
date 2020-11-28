#pragma once
#include "../../Model/Model/IModel.h"
#include <memory>

struct ModelComponent{

	ModelComponent(const std::shared_ptr<IModel>& model)
		:m_model{ model }{		
	}
	
	std::shared_ptr<IModel> m_model = nullptr;
	
};
