#include "OpenGLMesh.h"
#include <glad/glad.h>

OpenGL::OpenGLMesh::OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const std::shared_ptr<IShaderProgram>& shader_program)
	:m_vertices{ vertices },
	 m_indicies{ indices },
     m_texture_handler{ shader_program },
     m_vao{ 99 },
	 m_vbo{ 99 },
	 m_ebo{ 99 }{
    setup();	
}

void OpenGL::OpenGLMesh::setup(){

    // Create buffers/arrays
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(unsigned int), &m_indicies[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normals));

    // Vertex Textures	
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_tex_coords));

    // Vertex Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_tangent));

    // Vertex BitTangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_bitangent));

    glBindVertexArray(0);
	
}

void OpenGL::OpenGLMesh::draw() const{
    
    m_texture_handler.bind_textures();

	glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indicies.size()), GL_UNSIGNED_INT, 0); //TODO if draw is messed up try changing nullptr to 0.
    glBindVertexArray(0);

    m_texture_handler.unbind_textures();


}

void OpenGL::OpenGLMesh::destroy(){
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);
}

void OpenGL::OpenGLMesh::attach_diffuse_texture(const std::string& texture_name){
    m_texture_handler.attach_diffuse_texture(texture_name);
}

void OpenGL::OpenGLMesh::attach_normal_texture(const std::string& texture_name){
    m_texture_handler.attach_normal_texture(texture_name);
}

void OpenGL::OpenGLMesh::attach_specular_texture(const std::string& texture_name, const float shininess){
    m_texture_handler.attach_specular_texture(texture_name, shininess);
}


