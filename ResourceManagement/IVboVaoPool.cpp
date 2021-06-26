#include "IVboVaoPool.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../ResourceManagement/OpenGL/OpenGLVboVaoPool.h"
#include "../Utility/FatalError.h"

std::shared_ptr<IVboVaoPool> IVboVaoPool::m_pool_instance = nullptr;

std::shared_ptr<IVboVaoPool> IVboVaoPool::get_vbo_vao_pool(){
	std::shared_ptr<IVboVaoPool> pool{ nullptr };

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		pool = std::make_shared<OpenGL::OpenGLVboVaoPool>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan voxel updater does not exist!.");
	} else {
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return voxel updater.");
	}

	return pool;
}
