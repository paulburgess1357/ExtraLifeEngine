#include "OpenGLModel.h"

OpenGL::OpenGLModel::OpenGLModel(const OpenGLModelLoader& model_loader){
	// TODO e.g. m_mesh_vector = model_loader.get_loaded_mesh_vector();
}

void OpenGL::OpenGLModel::draw() const{
	for(const auto& mesh : m_mesh_vector){

		// TODO Activate shader program (likley in render function outside this loop)
		mesh.draw();
		
	}
}

