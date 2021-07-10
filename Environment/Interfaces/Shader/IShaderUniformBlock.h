#pragma once
#include "../../Matrix/ProjectionMatrix.h"
#include "../../Camera/Camera.h"
#include <memory>

class IShaderUniformBlock{
	
public:
	IShaderUniformBlock();
	IShaderUniformBlock(ProjectionMatrix* projection_matrix);
	virtual ~IShaderUniformBlock() = default;

	virtual void set_projection_view_block_matrix_values(Camera& camera) const = 0;
	virtual void set_camera_position_block_vector_values(Camera& camera) const = 0;
	
	virtual void update(Camera& camera) const = 0;
	virtual void destroy() const = 0;

	[[nodiscard]] static std::unique_ptr<IShaderUniformBlock> create_shader_uniform_block(ProjectionMatrix* projection_matrix);
	
protected:	
	static void check_projection_view_block_created();
	static void check_camera_position_block_created();
	static unsigned int m_ubo_matrices_handle;
	static unsigned int m_ubo_camera_handle;
	ProjectionMatrix* m_projection_matrix;		
};
