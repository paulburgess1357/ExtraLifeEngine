#include "OpenGLChunkManager.h"
#include "../Utility/Print.h"

void OpenGL::OpenGLChunkManager::load(const WorldPosition& m_world_position, const std::shared_ptr<IShaderProgram>& shader_program){	
	m_chunkmap[m_world_position] = std::make_shared<OpenGLChunk>(m_world_position, shader_program);
}

void OpenGL::OpenGLChunkManager::update(){
	for(const auto& chunk : m_chunkmap){
		chunk.second->update();
	}	
}

void OpenGL::OpenGLChunkManager::render(){
	for (const auto& chunk : m_chunkmap) {
		chunk.second->render();
	}
}