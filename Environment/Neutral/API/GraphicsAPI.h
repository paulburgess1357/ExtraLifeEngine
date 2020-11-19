#pragma once
#include "GraphicsAPIType.h"

class GraphicsAPI{
	
public:
	static GraphicsAPIType get_api();
	
private:
	GraphicsAPI() = default;
	static GraphicsAPIType m_api;
	
};

