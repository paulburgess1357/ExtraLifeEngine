#include "OpenGLCubeLoader.h"
#include "../../ResourceManagement/GraphicsConstants.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

CubeIDStruct OpenGL::OpenGLCubeLoader::load_cube_verticies() const {

	Print::print("Loading Cube Component Vertices");
	
	// Load/store CubeComponent Data
	unsigned int vbo_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int vao_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int ebo_id{ GraphicsConstants::UNINITIALIZED_VALUE };

	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	glGenVertexArrays(1, &vao_id);

	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_verticies_indexed), m_cube_verticies_indexed, GL_STATIC_DRAW);

	// Set up indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_all_cube_ebo_indices), m_all_cube_ebo_indices, GL_STATIC_DRAW);

	// Vertex Data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return CubeIDStruct{vbo_id, vao_id, ebo_id };
}

CubeIDStruct OpenGL::OpenGLCubeLoader::load_cube_normal_verticies() const {

	Print::print("Loading Cube Component Normal Vertices");
	
	// Load/store CubeComponent Data
	unsigned int vbo_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int vao_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int ebo_id{ GraphicsConstants::UNINITIALIZED_VALUE };

	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	glGenVertexArrays(1, &vao_id);

	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_verticies_normals_indexed), m_cube_verticies_normals_indexed, GL_STATIC_DRAW);

	// Set up indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_all_cube_ebo_indices), m_all_cube_ebo_indices, GL_STATIC_DRAW);
	
	// Vertex Data
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return CubeIDStruct{ vbo_id, vao_id, ebo_id };
}

CubeIDStruct OpenGL::OpenGLCubeLoader::load_cube_textured_verticies() const {

	Print::print("Loading Cube Component Textured Vertices");

	// Load/store CubeComponent Data
	unsigned int vbo_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int vao_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int ebo_id{ GraphicsConstants::UNINITIALIZED_VALUE };

	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	glGenVertexArrays(1, &vao_id);

	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_verticies_texture_indexed), m_cube_verticies_texture_indexed, GL_STATIC_DRAW);

	// Set up indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_all_cube_ebo_indices), m_all_cube_ebo_indices, GL_STATIC_DRAW);
	
	// Vertex Data
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture Coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return CubeIDStruct{ vbo_id, vao_id, ebo_id };
}

CubeIDStruct OpenGL::OpenGLCubeLoader::load_cube_normal_textured_verticies() const {

	Print::print("Loading Cube Component Textured Normal Vertices");
	
	// Load/store CubeComponent Data
	unsigned int vbo_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int vao_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int ebo_id{ GraphicsConstants::UNINITIALIZED_VALUE };

	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	glGenVertexArrays(1, &vao_id);

	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_verticies_normals_textures_indexed), m_cube_verticies_normals_textures_indexed, GL_STATIC_DRAW);

	// Set up indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_all_cube_ebo_indices), m_all_cube_ebo_indices, GL_STATIC_DRAW);
	
	// Vertex Data
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ITexture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return CubeIDStruct{ vbo_id, vao_id, ebo_id };
}

CubeIDStruct OpenGL::OpenGLCubeLoader::load_cubemap_verticies() const{

	// Load/store CubeComponent Data
	unsigned int vbo_id{ GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int vao_id{ GraphicsConstants::UNINITIALIZED_VALUE };

	glGenBuffers(1, &vbo_id);
	glGenVertexArrays(1, &vao_id);

	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cubemap_verticies), m_cubemap_verticies, GL_STATIC_DRAW);
	
	// Vertex Data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return CubeIDStruct{ vbo_id, vao_id, GraphicsConstants::UNINITIALIZED_VALUE };
	
}


void OpenGL::OpenGLCubeLoader::destroy(const CubeIDStruct cube_id_struct) const{
	glDeleteBuffers(1, &cube_id_struct.m_vbo_id);
	glDeleteBuffers(1, &cube_id_struct.m_ebo_id);
	glDeleteVertexArrays(1, &cube_id_struct.m_vao_id);
}
