#include "IShaderUniformBlock.h"
#include "../../Utility/FatalError.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../OpenGL/Shader/OpenGLUniformBlock.h"
#include "../../ResourceManagement/GraphicsConstants.h"

unsigned int IShaderUniformBlock::m_ubo_matrices_handle = GraphicsConstants::UNINITIALIZED_VALUE;
unsigned int IShaderUniformBlock::m_ubo_camera_handle = GraphicsConstants::UNINITIALIZED_VALUE;

void IShaderUniformBlock::check_projection_view_block_created() const {
	if (m_ubo_matrices_handle == 99) {
		FatalError::fatal_error("Projection view uniform block handle is 99 and has not been properly initialized!");
	}
}

void IShaderUniformBlock::check_camera_position_block_created() const{
	if (m_ubo_camera_handle == 99) {
		FatalError::fatal_error("Camera uniform block handle is 99 and has not been properly initialized!");
	}
}

std::shared_ptr<IShaderUniformBlock> IShaderUniformBlock::create_shader_uniform_block(){

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLUniformBlock>();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<IShaderUniformBlock> uniform_block = nullptr;
		FatalError::fatal_error("Vulkan shader uniform block does not exist!.");
		return uniform_block;
	}

	FatalError::fatal_error("Unknown Graphics API Type.  Cannot return uniform block.");
	std::shared_ptr<IShaderUniformBlock> uniform_block = nullptr;
	return uniform_block;
}
