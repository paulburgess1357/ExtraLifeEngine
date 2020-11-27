#include "OpenGLModel.h"

OpenGL::OpenGLModel::OpenGLModel(const std::shared_ptr<IShaderProgram>& shader_program, OpenGLModelLoaderFromFile& model_loader)
	:IModel(shader_program){

	model_loader.set_shader_program(m_shader_program);
	m_mesh_vector = model_loader.load();
	
}

void OpenGL::OpenGLModel::draw() const{
	for(const auto& mesh : m_mesh_vector){

		// TODO Activate shader program (likley in render function outside this loop)
		mesh.draw();
		
	}
}

void OpenGL::OpenGLModel::destroy(){
	for (auto& mesh : m_mesh_vector){
		mesh.destroy();
	}
	m_mesh_vector.clear();
}


