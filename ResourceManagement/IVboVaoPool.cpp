#include "IVboVaoPool.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../ResourceManagement/OpenGL/OpenGLVboVaoPool.h"
#include "../Utility/FatalError.h"

std::unique_ptr<IVboVaoPool> IVboVaoPool::create_vbo_vao_pool() {
	std::unique_ptr<IVboVaoPool> pool{ nullptr };

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		pool = std::make_unique<OpenGL::OpenGLVboVaoPool>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan vbo_vao pool creator does not exist!.");
	} else {
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return vbo_vao pool.");
	}

	return pool;
}
