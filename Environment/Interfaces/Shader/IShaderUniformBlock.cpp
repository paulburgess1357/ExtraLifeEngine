#include "IShaderUniformBlock.h"
#include "../../Utility/FatalError.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../OpenGL/Shader/OpenGLUniformBlock.h"
#include "../../ResourceManagement/GraphicsConstants.h"

unsigned int IShaderUniformBlock::m_ubo_matrices_handle = GraphicsConstants::UNINITIALIZED_VALUE;
unsigned int IShaderUniformBlock::m_ubo_camera_handle = GraphicsConstants::UNINITIALIZED_VALUE;

IShaderUniformBlock::IShaderUniformBlock()
	:m_projection_matrix{ nullptr }{	
}

IShaderUniformBlock::IShaderUniformBlock(ProjectionMatrix* projection_matrix)
	:m_projection_matrix{ projection_matrix }{	
}

void IShaderUniformBlock::check_projection_view_block_created() const {
	if (m_ubo_matrices_handle == GraphicsConstants::UNINITIALIZED_VALUE) {
		FatalError::fatal_error("Projection view uniform block handle is: " + std::to_string(GraphicsConstants::UNINITIALIZED_VALUE) + " and has not been properly initialized!");
	}
}

void IShaderUniformBlock::check_camera_position_block_created() const{
	if (m_ubo_camera_handle == GraphicsConstants::UNINITIALIZED_VALUE) {
		FatalError::fatal_error("Camera uniform block handle is: " + std::to_string(GraphicsConstants::UNINITIALIZED_VALUE) + " and has not been properly initialized!");
	}
}

std::unique_ptr<IShaderUniformBlock> IShaderUniformBlock::create_shader_uniform_block(ProjectionMatrix* projection_matrix){

	std::unique_ptr<IShaderUniformBlock> uniform_block{ nullptr };
	
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		uniform_block = std::make_unique<OpenGL::OpenGLUniformBlock>(projection_matrix);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan shader uniform block does not exist!.");
	} else{
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return uniform block.");
	}
	return uniform_block;
}
