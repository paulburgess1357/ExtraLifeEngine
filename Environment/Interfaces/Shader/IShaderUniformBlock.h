#pragma once
#include "IShaderProgram.h"
#include "../../Camera/Camera.h"
#include <memory>

class IShaderUniformBlock{
	
public:
	virtual ~IShaderUniformBlock() = default;

	virtual void create_projection_view_block() = 0;
	virtual void link_projection_view_block_to_shader(std::shared_ptr<IShaderProgram> shader_program) = 0;
	virtual void set_projection_view_block_matrix_values(Camera& camera) const = 0;

	virtual void create_camera_position_block() = 0;
	virtual void link_camera_position_block_to_shader(std::shared_ptr<IShaderProgram> shader_program) = 0;
	virtual void set_camera_position_block_vector_values(Camera& camera) const = 0;
	
	virtual void update(Camera& camera) const = 0;
	virtual void destroy() const = 0;
	
protected:	
	virtual void check_projection_view_block_created() const;
	virtual void check_camera_position_block_created() const;
	static unsigned int m_ubo_matrices_handle;
	static unsigned int m_ubo_camera_handle;
	
};