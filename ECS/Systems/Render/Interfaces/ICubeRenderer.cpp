#include "ICubeRenderer.h"
#include "../OpenGL/OpenGLCubeRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

std::shared_ptr<ICubeRenderer> ICubeRenderer::get_cube_renderer(){

	std::shared_ptr<ICubeRenderer> renderer { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		renderer = std::make_shared<OpenGL::OpenGLCubeRenderer>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan cube renderer does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return cube renderer.");
	}
	
	return renderer;
	
}
