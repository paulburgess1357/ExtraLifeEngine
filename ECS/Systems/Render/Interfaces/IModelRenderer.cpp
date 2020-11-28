#include "IModelRenderer.h"
#include "../OpenGL/OpenGLModelRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

std::shared_ptr<IModelRenderer> IModelRenderer::get_model_renderer() {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLModelRenderer>();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<IModelRenderer> model_renderer = nullptr;
		FatalError::fatal_error("Vulkan model renderer does not exist!.");
		return model_renderer;
	}

	FatalError::fatal_error("Unknown Graphics API Type.  Cannot return uniform block.");
	std::shared_ptr<IModelRenderer> cube_renderer = nullptr;
	return cube_renderer;

}