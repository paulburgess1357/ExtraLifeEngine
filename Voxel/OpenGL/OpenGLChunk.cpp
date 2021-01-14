#include "OpenGLChunk.h"
#include "../Neutral/VertexAndNormals.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position, 
	const std::shared_ptr<IShaderProgram>& shader_program,
	const std::shared_ptr<ChunkManager>& chunk_manager)
	:IChunk(starting_world_position, shader_program),
	 m_vbo{ 99 },
	 m_vao{ 99 },
	 m_chunkmanager{ chunk_manager }{
	 initialize_vbo_vao();
}

OpenGL::OpenGLChunk::~OpenGLChunk(){
	Print::print("Destroying Chunk Data");
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void OpenGL::OpenGLChunk::initialize_vbo_vao(){
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
	m_shader_program->set_uniform("normal_matrix", m_normal_matrix);
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
	
	// When creating chunks larger than 15x15x15 a vector is required.
	// It is possible to create this vertex using:
	// VertexAndNormals vertex[CX * CY * CZ * 6 * 6];  However, this is
	// created on the stack and you will quickly run into memory issues when
	// creating chunks larger than 15x15x15.
	
	std::vector<VertexAndNormals> vertex;	
	for(signed char x = 0; x < CX; x++){
		for(signed char y = 0; y < CY; y++){
			for(signed char z = 0; z < CZ; z++){				
				const signed char type = m_block_types[x][y][z];
				
				// Skip Empty Blocks
				if(type == 0){
					continue;
				}			
				
				//TODO Values on the edges of chunks are being drawn, even
				//TODO if there is overlap from one chunk to another chunk.
				//TODO I need to be able to reference the cube type in adjacent
				//TODO chunks.  Note that the (x == 0) (y == 0) (y ++ CY -1), etc
				//TODO is also happening here (without that arguemnt I wouldn't draw the
				//TODO chunk edge).
				
				// left face (negative x)
				// E.g. if x is > 0 and the block to the left does not exist, draw square
				if ((x > 0 && m_block_types[x - 1][y][z] == 0) || (x == 0)) {
					vertex.emplace_back(x, y, z, type, -1, 0, 0); // bottom left
					vertex.emplace_back(x, y, z + 1, type, -1, 0, 0); // bottom right
					vertex.emplace_back(x, y + 1, z, type, -1, 0, 0); // top left
					vertex.emplace_back(x, y + 1, z, type, -1, 0, 0); // top left
					vertex.emplace_back(x, y, z + 1, type, -1, 0, 0); // bottom right
					vertex.emplace_back(x, y + 1, z + 1, type, -1, 0, 0); // top right
				}

				// right face (positive x)
				// if x is < CX and the block to the right does not exist, draw square
				 if ((x < CX - 1 && m_block_types[x + 1][y][z] == 0) || (x == CX - 1)) {
					vertex.emplace_back(x + 1, y,     z + 1, type, 1, 0, 0); // bottom left
					vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
					vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
					vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
					vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
					vertex.emplace_back(x + 1, y + 1, z,     type, 1, 0, 0); // top right
				}

				// front face (positive z)
				//if ((z > 0 && m_block_types[x][y][z - 1] == 0) || (z == 0)) {
				if ((z < CZ - 1 && m_block_types[x][y][z + 1] == 0) || (z == CZ - 1)) {
					vertex.emplace_back(x, y, z + 1, type, 0, 0, 1); // bottom left
					vertex.emplace_back(x + 1, y, z + 1, type, 0, 0, 1); // bottom right
					vertex.emplace_back(x, y + 1, z + 1, type, 0, 0, 1); // top left
					vertex.emplace_back(x, y + 1, z + 1, type, 0, 0, 1); // top left
					vertex.emplace_back(x + 1, y, z + 1, type, 0, 0, 1); // bottom right
					vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 0, 1); // top right
				}

				// back face (negative z)
				 if ((z > 0 && m_block_types[x][y][z - 1] == 0) || (z == 0)) {
					vertex.emplace_back(x + 1, y,     z,     type, 0, 0, -1); // bottom left
					vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
					vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
					vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
					vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
					vertex.emplace_back(x,     y + 1, z,     type, 0, 0, -1); // top right
				}

				// top face (positive y)
				 if((y < CY - 1 && m_block_types[x][y + 1][z] == 0) || (y == CY - 1)){
					vertex.emplace_back(x, y + 1, z + 1, type, 0, 1, 0); // bottom left
					vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
					vertex.emplace_back(x, y + 1, z, type, 0, 1, 0); // top left
					vertex.emplace_back(x, y + 1, z, type, 0, 1, 0); // top left
					vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
					vertex.emplace_back(x + 1, y + 1, z, type, 0, 1, 0); // top right
				}

				// bottom face (negative y)
				 if ((y > 0 && m_block_types[x][y - 1][z] == 0) || (y == 0)) {
					vertex.emplace_back(x,     y,     z,     type, 0, -1, 0); // bottom left
					vertex.emplace_back(x + 1, y,     z,     type, 0, -1, 0); // bottom right
					vertex.emplace_back(x,     y,     z + 1, type, 0, -1, 0); // top left
					vertex.emplace_back(x,     y,     z + 1, type, 0, -1, 0); // top left
					vertex.emplace_back(x + 1, y,     z,     type, 0, -1, 0); // bottom right
					vertex.emplace_back(x + 1, y,     z + 1, type, 0, -1, 0); // top right
				}
			}			
		}		
	}	

	m_vertex_qty = static_cast<int>(vertex.size());

	// Bind Buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Store Data
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexAndNormals), &vertex[0], GL_STATIC_DRAW);
	
	// Vertex Data
	glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 7 * sizeof(signed char), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_BYTE, GL_FALSE, 7 * sizeof(signed char), (void*) (4 * sizeof(signed char)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

