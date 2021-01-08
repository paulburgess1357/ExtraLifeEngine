#include "OpenGLChunkManager.h"

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

//void OpenGL::OpenGLChunkManager::load(const std::shared_ptr<IShaderProgram>& shader_program){
//	for(int x = 0; x < SCX; x++){
//		for(int y = 0; y < SCY; y++){
//			for(int z = 0; z < SCZ; z++){
//				m_chunkmap[x][y][z] = new OpenGLChunk(WorldPosition(x * SCX, y * SCY, z*SCZ), shader_program);
//			}
//		}
//	}
//}
//
//void OpenGL::OpenGLChunkManager::update(){
//	for (int x = 0; x < SCX; x++) {
//		for (int y = 0; y < SCY; y++) {
//			for (int z = 0; z < SCZ; z++) {
//				m_chunkmap[x][y][z]->update();
//			}
//		}
//	}
//}
//
//void OpenGL::OpenGLChunkManager::render(){
//	for (int x = 0; x < SCX; x++) {
//		for (int y = 0; y < SCY; y++) {
//			for (int z = 0; z < SCZ; z++) {
//				m_chunkmap[x][y][z]->render();
//			}
//		}
//	}
//}
