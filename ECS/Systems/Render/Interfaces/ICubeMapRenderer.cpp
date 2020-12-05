#include "ICubeMapRenderer.h"
#include "../OpenGL/OpenGLCubeMapRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

std::shared_ptr<ICubeMapRenderer> ICubeMapRenderer::get_cube_renderer(){

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLCubeMapRenderer>();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<ICubeMapRenderer> cubemap_renderer = nullptr;
		FatalError::fatal_error("Vulkan cubemap renderer does not exist!.");
		return cubemap_renderer;
	}

	FatalError::fatal_error("Unknown Graphics API Type.  Cannot return cubemap renderer.");
	std::shared_ptr<ICubeMapRenderer> cubemap_renderer = nullptr;
	return cubemap_renderer;
	
}
