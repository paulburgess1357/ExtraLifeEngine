#include "OpenGLVboVaoPool.h"
#include "OpenGLConstants.h"
#include <glad/glad.h>
#include <iostream>

std::shared_ptr<IVboVaoPool> OpenGL::OpenGLVboVaoPool::get_instance(){
	if(m_pool_instance == nullptr){
		m_pool_instance = std::make_shared<OpenGLVboVaoPool>();
	}
	return m_pool_instance;
}

std::pair<unsigned, unsigned> OpenGL::OpenGLVboVaoPool::get_resource(){
	if(m_vbo_vao_resources.empty()){
		
		unsigned int vbo { OpenGL::UNINITIALIZED_CHUNK_VALUE };
		unsigned int vao { OpenGL::UNINITIALIZED_CHUNK_VALUE };

		glGenBuffers(1, &vbo);
		glGenVertexArrays(1, &vao);
		return std::make_pair(vbo, vao);
						
	}
	std::pair<unsigned int, unsigned int> result = m_vbo_vao_resources.front();
	m_vbo_vao_resources.pop();
	return result;
	
}

void OpenGL::OpenGLVboVaoPool::return_resource(std::pair<unsigned, unsigned> resource){
	// TODO Call glDelete here?
	m_vbo_vao_resources.emplace(resource);
}


