#include "ICubeRenderer.h"
#include "../OpenGL/OpenGLCubeRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

std::shared_ptr<ICubeRenderer> ICubeRenderer::get_cube_renderer(){

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLCubeRenderer>();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<ICubeRenderer> cube_renderer = nullptr;
		FatalError::fatal_error("Vulkan cube renderer does not exist!.");
		return cube_renderer;
	}

	FatalError::fatal_error("Unknown Graphics API Type.  Cannot return cube renderer.");
	std::shared_ptr<ICubeRenderer> cube_renderer = nullptr;
	return cube_renderer;
	
}
