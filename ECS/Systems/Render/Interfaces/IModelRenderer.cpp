#include "IModelRenderer.h"
#include "../OpenGL/OpenGLModelRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

std::shared_ptr<IModelRenderer> IModelRenderer::get_model_renderer() {

	std::shared_ptr<IModelRenderer> renderer { nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		renderer = std::make_shared<OpenGL::OpenGLModelRenderer>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan model renderer does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return uniform block.");
	}

	return renderer;

}