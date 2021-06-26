#include "OpenGLVboVaoPool.h"

std::shared_ptr<VboVaoPool> OpenGL::OpenGLVboVaoPool::get_instance(){
	if(m_pool_instance == nullptr){
		m_pool_instance = std::make_shared<OpenGLVboVaoPool>();
	}
	return m_pool_instance;
}

std::pair<unsigned, unsigned> OpenGL::OpenGLVboVaoPool::get_resource(){
	if(m_vbo_vao_resources.empty()){
		// Create resource and return
		
		
	} else{
		std::pair<unsigned int, unsigned int> result = m_vbo_vao_resources.front();
		m_vbo_vao_resources.pop();
	}
}

std::pair<int, int> OpenGL::OpenGLVboVaoPool::return_resource(std::pair<unsigned, unsigned> resource){
	// Call glDelete here?
	m_vbo_vao_resources.emplace(resource);
}


