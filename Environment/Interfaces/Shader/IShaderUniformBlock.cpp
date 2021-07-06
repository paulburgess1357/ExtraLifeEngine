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

std::unique_ptr<IShaderUniformBlock> IShaderUniformBlock::create_shader_uniform_block(){

	std::unique_ptr<IShaderUniformBlock> uniform_block{ nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		uniform_block = std::make_unique<OpenGL::OpenGLUniformBlock>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan shader uniform block does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return uniform block.");
	}
	return uniform_block;
}
