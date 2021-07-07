#include "OpenGLMesh.h"
#include <glad/glad.h>
#include "../../ResourceManagement/GraphicsConstants.h"
#include "../../Utility/Print.h"

OpenGL::OpenGLMesh::OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, IShaderProgram& shader_program)
    :IMesh{ std::move(vertices), std::move(indices) },
     m_vao{ GraphicsConstants::UNINITIALIZED_VALUE },
	 m_vbo{ GraphicsConstants::UNINITIALIZED_VALUE },
	 m_ebo{ GraphicsConstants::UNINITIALIZED_VALUE }{
     m_texture_handler = std::make_shared<OpenGLTextureHandler>(shader_program);	
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

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

void OpenGL::OpenGLMesh::destroy(){
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);
}

void OpenGL::OpenGLMesh::attach_diffuse_texture(const ITexture& texture){
    m_texture_handler->attach_diffuse_texture(texture);
}

void OpenGL::OpenGLMesh::attach_normal_texture(const ITexture& texture){
    m_texture_handler->attach_normal_texture(texture);
}

void OpenGL::OpenGLMesh::attach_specular_texture(const ITexture& texture, const float shininess){
    m_texture_handler->attach_specular_texture(texture, shininess);
}

unsigned int OpenGL::OpenGLMesh::get_vao() const{
    return m_vao;
}
