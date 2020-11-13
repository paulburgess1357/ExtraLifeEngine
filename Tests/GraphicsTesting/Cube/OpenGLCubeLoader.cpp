#include "OpenGLCubeLoader.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

std::pair<unsigned int, unsigned int> OpenGL::OpenGLCubeLoader::load_cube_verticies() const {

	Print::print("Loading CubeComponent Vertices");
	
	// Load/store CubeComponent Data
	unsigned int vbo_id{ 99 };
	unsigned int vao_id{ 99 };

	glGenBuffers(1, &vbo_id);
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_verticies), m_cube_verticies, GL_STATIC_DRAW);

	// Vertex Data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return std::make_pair(vbo_id, vao_id);
}


std::pair<unsigned int, unsigned int> OpenGL::OpenGLCubeLoader::load_cube_normal_verticies() const {

	Print::print("Loading CubeComponent Normal Vertices");
	
	// Load/store CubeComponent Data
	unsigned int vbo_id{ 99 };
	unsigned int vao_id{ 99 };

	glGenBuffers(1, &vbo_id);
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_verticies_normals), m_cube_verticies_normals, GL_STATIC_DRAW);

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

	return std::make_pair(vbo_id, vao_id);
}

std::pair<unsigned int, unsigned int> OpenGL::OpenGLCubeLoader::load_cube_normal_textured_verticies() const {

	Print::print("Loading CubeComponent Textured Normal Vertices");
	
	// Load/store CubeComponent Data
	unsigned int vbo_id{ 99 };
	unsigned int vao_id{ 99 };

	glGenBuffers(1, &vbo_id);
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_verticies_normals_textures), m_cube_verticies_normals_textures, GL_STATIC_DRAW);

	// Vertex Data
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return std::make_pair(vbo_id, vao_id);
}

void OpenGL::OpenGLCubeLoader::destory(const unsigned int vbo_id, const unsigned int vao_id) const{
	glDeleteBuffers(1, &vbo_id);
	glDeleteVertexArrays(1, &vao_id);
}
