#pragma once
#include <string>
#include "../../ResourceManagement/GraphicsConstants.h"

struct TextureShaderData {

	TextureShaderData()
		:m_texture_name_in_shader{ "Texture Shader Data Uninitialized" }{		
	}
	
	TextureShaderData(const std::string& texture_name_in_shader, 
					  const unsigned int tex_unit, 
					  const unsigned int tex_handle)
		:m_texture_name_in_shader(texture_name_in_shader),
		 m_tex_unit{ tex_unit },
		 m_tex_handle{ tex_handle}{
		
	}

	TextureShaderData(const std::string& texture_name_in_shader,
		const unsigned int tex_unit,
		const unsigned int tex_handle,
	    float shininess)
		:m_texture_name_in_shader(texture_name_in_shader),
		m_tex_unit{ tex_unit },
		m_tex_handle{ tex_handle },
		m_shininess{ shininess }{

	}
	
	std::string m_texture_name_in_shader;
	unsigned int m_tex_unit { GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int m_tex_handle{ GraphicsConstants::UNINITIALIZED_VALUE };
	float m_shininess{ 16.0f };
};
