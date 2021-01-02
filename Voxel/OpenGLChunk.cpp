#include "OpenGLChunk.h"

OpenGL::OpenGLChunk::OpenGLChunk()
	:m_block_types{},
	 m_vbo{ 99 },
	 m_block_qty{ 0 },
	 m_contents_changed{ true }{
	glGenBuffers(1, &m_vbo);		
}

OpenGL::OpenGLChunk::~OpenGLChunk(){
	glDeleteBuffers(1, &m_vbo);
}

uint8_t OpenGL::OpenGLChunk::get(const int x, const int y, const int z) const{
	return m_block_types[x][y][z];
}

void OpenGL::OpenGLChunk::set(const int x, const int y, const int z, uint8_t type){
	m_block_types[x][y][z] = type;
	m_contents_changed = true;
}

void OpenGL::OpenGLChunk::render(){
	if(m_contents_changed){
		update();
	}
	// Render VBO here
}

void OpenGL::OpenGLChunk::update() {
	m_contents_changed = false;
	byte4 vertex[CX * CY * CZ * 6 * 6];	

	int i = 0;
	for(int x = 0; x < CX; x++){
		for(int y = 0; y < CY; y++){
			for(int z = 0; z < CZ; z++){

				uint8_t type = m_block_types[x][y][z];
				
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

	m_block_qty = i;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_block_qty * sizeof *vertex, vertex, GL_STATIC_DRAW);
	
}

