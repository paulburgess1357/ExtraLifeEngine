#include "OpenGLVboVaoPool.h"
#include "OpenGLConstants.h"
#include "../../Utility/FatalError.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

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
	check_vbo_vao_value(resource);	
	// TODO Call glDelete here?
	m_vbo_vao_resources.emplace(resource);
}

void OpenGL::OpenGLVboVaoPool::check_vbo_vao_value(const std::pair<unsigned int, unsigned int>& vbo_vao){
	if(vbo_vao.first == OpenGL::UNINITIALIZED_CHUNK_VALUE || vbo_vao.second == OpenGL::UNINITIALIZED_CHUNK_VALUE){
		FatalError::fatal_error("Returned VBO or VAO value is equal to the uninitialized chunk value: " + std::to_string(OpenGL::UNINITIALIZED_CHUNK_VALUE));
		Print::print("VBO: " + std::to_string(vbo_vao.first));
		Print::print("VAO: " + std::to_string(vbo_vao.second));
	}
}



