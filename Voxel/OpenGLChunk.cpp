#include "OpenGLChunk.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Utility/Print.h"

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position, const std::shared_ptr<IShaderProgram>& shader_program)
	:m_block_types{},
	 m_vbo{ 99 },
	 m_vao{ 99 },
	 m_vertex_qty{ 0 },
	 m_update_required{ true },
     m_model_matrix{ glm::translate(glm::mat4(1), starting_world_position.get_vec3()) },
     m_shader_program { shader_program }{

	 initialize();
	 Print::print("World Position: " + std::to_string(starting_world_position.x) + ";" + std::to_string(starting_world_position.y) + ";" + std::to_string(starting_world_position.z));
}

OpenGL::OpenGLChunk::~OpenGLChunk(){
	Print::print("Destroying Chunk Data");
	glDeleteBuffers(1, &m_vbo);
}

uint8_t OpenGL::OpenGLChunk::get(const int x, const int y, const int z) const{
	return m_block_types[x][y][z];
}

void OpenGL::OpenGLChunk::set(const int x, const int y, const int z, uint8_t type){
	m_block_types[x][y][z] = type;
	m_update_required = true;
}

void OpenGL::OpenGLChunk::initialize(){
	Print::print("Initializing Chunk VBO and VAO");
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);
}

void OpenGL::OpenGLChunk::render() const{

	// Skip drawing empty chunks
	if(m_vertex_qty == 0){
		return;
	}

	m_shader_program->set_uniform("model_matrix", m_model_matrix);
	m_shader_program->bind();
						
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertex_qty);
	glBindVertexArray(0);

	m_shader_program->unbind();	
}

void OpenGL::OpenGLChunk::update() {

	if(!m_update_required){
		return;
	}

	Print::print("Loading Chunk Data...");
	
	m_update_required = false;
	byte4 vertex[CX * CY * CZ * 6 * 6];	

	int i = 0;
	for(int x = 0; x < CX; x++){
		for(int y = 0; y < CY; y++){
			for(int z = 0; z < CZ; z++){
				uint8_t type = m_block_types[x][y][z];

				type = 1;
				
				// Skip Empty Blocks
				if(!type){
					continue;
				}
				
				// left face (negative x)
				vertex[i++] = byte4(x,     y,     z,     type); // bottom left
				vertex[i++] = byte4(x,     y,     z + 1, type); // bottom right
				vertex[i++] = byte4(x,     y + 1, z,     type); // top left
				vertex[i++] = byte4(x,     y + 1, z,     type); // top left
				vertex[i++] = byte4(x,     y,     z + 1, type); // bottom right
				vertex[i++] = byte4(x,     y + 1, z + 1, type); // top right

				// right face (positive x)
				vertex[i++] = byte4(x + 1, y,     z + 1, type); // bottom left
				vertex[i++] = byte4(x + 1, y,     z,     type); // bottom right
				vertex[i++] = byte4(x + 1, y + 1, z + 1, type); // top left
				vertex[i++] = byte4(x + 1, y + 1, z + 1, type); // top left
				vertex[i++] = byte4(x + 1, y,     z,     type); // bottom right
				vertex[i++] = byte4(x + 1, y + 1, z,     type); // top right

				// front face (positive z)
				vertex[i++] = byte4(x,     y,     z + 1, type); // bottom left
				vertex[i++] = byte4(x + 1, y,     z + 1, type); // bottom right
				vertex[i++] = byte4(x,     y + 1, z + 1, type); // top left
				vertex[i++] = byte4(x,     y + 1, z + 1, type); // top left
				vertex[i++] = byte4(x + 1, y,     z + 1, type); // bottom right
				vertex[i++] = byte4(x + 1, y + 1, z + 1, type); // top right

				// back face (negative z)
				vertex[i++] = byte4(x + 1, y,     z,     type); // bottom left
				vertex[i++] = byte4(x,     y,     z,     type); // bottom right
				vertex[i++] = byte4(x + 1, y + 1, z,     type); // top left
				vertex[i++] = byte4(x + 1, y + 1, z,     type); // top left
				vertex[i++] = byte4(x,     y,     z,     type); // bottom right
				vertex[i++] = byte4(x,     y + 1, z,     type); // top right

				// top face (positive y)
				vertex[i++] = byte4(x,     y + 1, z + 1, type); // bottom left
				vertex[i++] = byte4(x + 1, y + 1, z + 1, type); // bottom right
				vertex[i++] = byte4(x,     y + 1, z,     type); // top left
				vertex[i++] = byte4(x,     y + 1, z,     type); // top left
				vertex[i++] = byte4(x + 1, y + 1, z + 1, type); // bottom right
				vertex[i++] = byte4(x + 1, y + 1, z,     type); // top right

				// bottom face (negative y)
				vertex[i++] = byte4(x,     y,     z,     type); // bottom left
				vertex[i++] = byte4(x + 1, y,     z,     type); // bottom right
				vertex[i++] = byte4(x,     y,     z + 1, type); // top left
				vertex[i++] = byte4(x,     y,     z + 1, type); // top left
				vertex[i++] = byte4(x + 1, y,     z,     type); // bottom right
				vertex[i++] = byte4(x + 1, y,     z + 1, type); // top right								
			}			
		}		
	}

	m_vertex_qty = i;

	// Bind Buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Store Data
	glBufferData(GL_ARRAY_BUFFER, m_vertex_qty * sizeof *vertex, vertex, GL_STATIC_DRAW);
	
	// Vertex Data
	glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, sizeof(byte4), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

