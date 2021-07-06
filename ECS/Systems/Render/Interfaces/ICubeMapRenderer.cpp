#include "ICubeMapRenderer.h"
#include "../OpenGL/OpenGLCubeMapRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

std::unique_ptr<ICubeMapRenderer> ICubeMapRenderer::get_cube_renderer(){

	std::unique_ptr<ICubeMapRenderer> renderer { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		renderer = std::make_unique<OpenGL::OpenGLCubeMapRenderer>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN){
		FatalError::fatal_error("Vulkan cubemap renderer does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return cubemap renderer.");
	}

	return renderer;
	
}
