#include "IShaderUniformBlock.h"
#include "../../Utility/FatalError.h"

unsigned int IShaderUniformBlock::m_ubo_matrices_handle = 99;
unsigned int IShaderUniformBlock::m_ubo_camera_handle = 99;

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
