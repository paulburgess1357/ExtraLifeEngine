#include "GraphicsAPI.h"

GraphicsAPIType GraphicsAPI::m_api = GraphicsAPIType::OPENGL;

GraphicsAPIType GraphicsAPI::get_api(){
	return m_api;
}
