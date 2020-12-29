#include "ICubeLoader.h"
#include "OpenGLCubeLoader.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"

// CounterClockwise Winding Order

const float ICubeLoader::m_cube_verticies[108] = {

     // back face
     0.5f, -0.5f, -0.5f, // bottom left	
    -0.5f, -0.5f, -0.5f, // bottom right
    -0.5f,  0.5f, -0.5f, // top right
    -0.5f,  0.5f, -0.5f, // top right		 
	 0.5f,  0.5f, -0.5f, // top left			
     0.5f, -0.5f, -0.5f, // bottom left	

     // front face
	-0.5f, -0.5f,  0.5f, // bottom left
	 0.5f, -0.5f,  0.5f, // bottom right
	 0.5f,  0.5f,  0.5f, // top right
	 0.5f,  0.5f,  0.5f, // top right
	-0.5f,  0.5f,  0.5f, // top left
	-0.5f, -0.5f,  0.5f, // bottom left

     // left face
    -0.5f, -0.5f, -0.5f, // bottom left
    -0.5f, -0.5f,  0.5f, // bottom right
	-0.5f,  0.5f,  0.5f, // top right
	-0.5f,  0.5f,  0.5f, // top right	
    -0.5f,  0.5f, -0.5f, // top left		
	-0.5f, -0.5f, -0.5f, // bottom left				

     // right face		 		 		 	     
	 0.5f, -0.5f,  0.5f, // bottom left
     0.5f, -0.5f, -0.5f, // bottom right
     0.5f,  0.5f, -0.5f, // top right
     0.5f,  0.5f, -0.5f, // top right	
	 0.5f,  0.5f,  0.5f, // top left
	 0.5f, -0.5f,  0.5f, // bottom left

	 // bottom face
	-0.5f, -0.5f, -0.5f, // bottom left
	 0.5f, -0.5f, -0.5f, // bottom right
	 0.5f, -0.5f,  0.5f, // top right
	 0.5f, -0.5f,  0.5f, // top right
	-0.5f, -0.5f,  0.5f, // top left
	-0.5f, -0.5f, -0.5f, // bottom left

    // top face
	-0.5f,  0.5f,  0.5f, // bottom left
	 0.5f,  0.5f,  0.5f, // bottom right
     0.5f,  0.5f, -0.5f, // top right
     0.5f,  0.5f, -0.5f, // top right	
	-0.5f,  0.5f, -0.5f, // top left
    -0.5f,  0.5f,  0.5f, // bottom left
};

const float ICubeLoader::m_cube_verticies_texture[180] = {

    // Vertices                 // Texture Coordinates
	// back face
	 0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left	
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, // bottom right
	-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right
	-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right		 
	 0.5f,  0.5f, -0.5f,		0.0f, 1.0f, // top left			
	 0.5f, -0.5f, -0.5f,		0.0f, 0.0f // bottom left	

	 // front face
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, // bottom left
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f, // bottom right
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, // top right
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, // top right
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, // top left
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, // bottom left

	 // left face
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left
	-0.5f, -0.5f,  0.5f,		1.0f, 0.0f, // bottom right
	-0.5f,  0.5f,  0.5f,		1.0f, 1.0f, // top right
	-0.5f,  0.5f,  0.5f,		1.0f, 1.0f, // top right	
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, // top left		
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left				

	 // right face		 		 		 	     
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, // bottom left
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, // bottom right
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right	
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, // top left
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, // bottom left

	 // bottom face
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, // bottom right
	 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, // top right
	 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, // top right
	-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, // top left
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left

	// top face
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, // bottom left
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f, // bottom right
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right	
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, // top left
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, // bottom left
};

const float ICubeLoader::m_cube_verticies_normals[216] = {

    // Verticies               // Normals

    // back face
    0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f, // bottom left	
   -0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f, // bottom right
   -0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f, // top right
   -0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f, // top right
    0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f, // top left
    0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f, // bottom left	

    // front face
   -0.5f, -0.5f,  0.5f,		   0.0f,  0.0f, 1.0f, // bottom left
    0.5f, -0.5f,  0.5f,		   0.0f,  0.0f, 1.0f, // bottom right
    0.5f,  0.5f,  0.5f,		   0.0f,  0.0f, 1.0f, // top right
    0.5f,  0.5f,  0.5f,		   0.0f,  0.0f, 1.0f, // top right
   -0.5f,  0.5f,  0.5f,		   0.0f,  0.0f, 1.0f, // top left
   -0.5f, -0.5f,  0.5f,		   0.0f,  0.0f, 1.0f, // bottom left

   // left face
   -0.5f, -0.5f, -0.5f,		  -1.0f,  0.0f,  0.0f, // bottom left
   -0.5f, -0.5f,  0.5f,		  -1.0f,  0.0f,  0.0f, // bottom right
   -0.5f,  0.5f,  0.5f,		  -1.0f,  0.0f,  0.0f, // top right
   -0.5f,  0.5f,  0.5f,		  -1.0f,  0.0f,  0.0f, // top right	   
   -0.5f,  0.5f, -0.5f,		  -1.0f,  0.0f,  0.0f, // top left	   
   -0.5f, -0.5f, -0.5f,		  -1.0f,  0.0f,  0.0f, // bottom left

    // right face
	0.5f, -0.5f,  0.5f,		   1.0f,  0.0f,  0.0f, // bottom left
	0.5f, -0.5f, -0.5f,		   1.0f,  0.0f,  0.0f, // bottom right
	0.5f,  0.5f, -0.5f,		   1.0f,  0.0f,  0.0f, // top right
    0.5f,  0.5f, -0.5f,		   1.0f,  0.0f,  0.0f, // top right	
    0.5f,  0.5f,  0.5f,		   1.0f,  0.0f,  0.0f, // top left
    0.5f, -0.5f,  0.5f,		   1.0f,  0.0f,  0.0f, // bottom left

    // bottom face
   -0.5f, -0.5f, -0.5f,		   0.0f, -1.0f,  0.0f, // bottom left
    0.5f, -0.5f, -0.5f,		   0.0f, -1.0f,  0.0f, // bottom right
    0.5f, -0.5f,  0.5f,		   0.0f, -1.0f,  0.0f, // top right
    0.5f, -0.5f,  0.5f,		   0.0f, -1.0f,  0.0f, // top right
   -0.5f, -0.5f,  0.5f,		   0.0f, -1.0f,  0.0f, // top left
   -0.5f, -0.5f, -0.5f,		   0.0f, -1.0f,  0.0f, // bottom left

    // top face
   -0.5f,  0.5f,  0.5f,		   0.0f,  1.0f,  0.0f, // bottom left
	0.5f,  0.5f,  0.5f,		   0.0f,  1.0f,  0.0f, // bottom right
	0.5f,  0.5f, -0.5f,		   0.0f,  1.0f,  0.0f, // top right
    0.5f,  0.5f, -0.5f,		   0.0f,  1.0f,  0.0f, // top right		
   -0.5f,  0.5f, -0.5f,		   0.0f,  1.0f,  0.0f, // top left
   -0.5f,  0.5f,  0.5f,		   0.0f,  1.0f,  0.0f, // bottom left
};

const float ICubeLoader::m_cube_verticies_normals_textures[288] = {

	// Verticies               // Normals		     // Textures

	// back face
	0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     0.0f, 0.0f, // bottom left	
   -0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     1.0f, 0.0f, // bottom right
   -0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     1.0f, 1.0f, // top right
   -0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     1.0f, 1.0f, // top right
	0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     0.0f, 1.0f, // top left
	0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     0.0f, 0.0f, // bottom left	

	// front face
   -0.5f, -0.5f,  0.5f,		   0.0f,  0.0f, 1.0f,     0.0f, 0.0f, // bottom left
	0.5f, -0.5f,  0.5f,		   0.0f,  0.0f, 1.0f,     1.0f, 0.0f, // bottom right
	0.5f,  0.5f,  0.5f,		   0.0f,  0.0f, 1.0f,     1.0f, 1.0f, // top right
	0.5f,  0.5f,  0.5f,		   0.0f,  0.0f, 1.0f,     1.0f, 1.0f, // top right
   -0.5f,  0.5f,  0.5f,		   0.0f,  0.0f, 1.0f,     0.0f, 1.0f, // top left
   -0.5f, -0.5f,  0.5f,		   0.0f,  0.0f, 1.0f,     0.0f, 0.0f, // bottom left

   // left face
   -0.5f, -0.5f, -0.5f,		  -1.0f,  0.0f,  0.0f,     0.0f, 0.0f, // bottom left
   -0.5f, -0.5f,  0.5f,		  -1.0f,  0.0f,  0.0f,     1.0f, 0.0f, // bottom right
   -0.5f,  0.5f,  0.5f,		  -1.0f,  0.0f,  0.0f,     1.0f, 1.0f, // top right
   -0.5f,  0.5f,  0.5f,		  -1.0f,  0.0f,  0.0f,     1.0f, 1.0f, // top right	   
   -0.5f,  0.5f, -0.5f,		  -1.0f,  0.0f,  0.0f,     0.0f, 1.0f, // top left	   
   -0.5f, -0.5f, -0.5f,		  -1.0f,  0.0f,  0.0f,     0.0f, 0.0f, // bottom left

	// right face
	0.5f, -0.5f,  0.5f,		   1.0f,  0.0f,  0.0f,     0.0f, 0.0f, // bottom left
	0.5f, -0.5f, -0.5f,		   1.0f,  0.0f,  0.0f,     1.0f, 0.0f, // bottom right
	0.5f,  0.5f, -0.5f,		   1.0f,  0.0f,  0.0f,     1.0f, 1.0f, // top right
	0.5f,  0.5f, -0.5f,		   1.0f,  0.0f,  0.0f,     1.0f, 1.0f, // top right	
	0.5f,  0.5f,  0.5f,		   1.0f,  0.0f,  0.0f,     0.0f, 1.0f, // top left
	0.5f, -0.5f,  0.5f,		   1.0f,  0.0f,  0.0f,     0.0f, 0.0f, // bottom left

	// bottom face
   -0.5f, -0.5f, -0.5f,		   0.0f, -1.0f,  0.0f,     0.0f, 0.0f, // bottom left
	0.5f, -0.5f, -0.5f,		   0.0f, -1.0f,  0.0f,     1.0f, 0.0f, // bottom right
	0.5f, -0.5f,  0.5f,		   0.0f, -1.0f,  0.0f,     1.0f, 1.0f, // top right
	0.5f, -0.5f,  0.5f,		   0.0f, -1.0f,  0.0f,     1.0f, 1.0f, // top right
   -0.5f, -0.5f,  0.5f,		   0.0f, -1.0f,  0.0f,     0.0f, 1.0f, // top left
   -0.5f, -0.5f, -0.5f,		   0.0f, -1.0f,  0.0f,     0.0f, 0.0f, // bottom left

	// top face
   -0.5f,  0.5f,  0.5f,		   0.0f,  1.0f,  0.0f,     0.0f, 0.0f, // bottom left
	0.5f,  0.5f,  0.5f,		   0.0f,  1.0f,  0.0f,     1.0f, 0.0f, // bottom right
	0.5f,  0.5f, -0.5f,		   0.0f,  1.0f,  0.0f,     1.0f, 1.0f, // top right
	0.5f,  0.5f, -0.5f,		   0.0f,  1.0f,  0.0f,     1.0f, 1.0f, // top right		
   -0.5f,  0.5f, -0.5f,		   0.0f,  1.0f,  0.0f,     0.0f, 1.0f, // top left
   -0.5f,  0.5f,  0.5f,		   0.0f,  1.0f,  0.0f,     0.0f, 0.0f, // bottom left
};

const float ICubeLoader::m_cubemap_verticies[108] = {

	// Cubemap needs to be in clockwise winding order.  If its not,
	// face culling will prevent the texture from being visible

	// back face
   -1.0f, -1.0f, -1.0f, // bottom right
    1.0f, -1.0f, -1.0f, // bottom left   
   -1.0f,  1.0f, -1.0f, // top right
   -1.0f,  1.0f, -1.0f, // top right
	1.0f, -1.0f, -1.0f, // bottom left
    1.0f,  1.0f, -1.0f, // top left			 
    
	// left face
   -1.0f, -1.0f,  1.0f, // bottom right
   -1.0f, -1.0f, -1.0f, // bottom left	   
   -1.0f,  1.0f,  1.0f, // top right
   -1.0f,  1.0f,  1.0f, // top right
   -1.0f, -1.0f, -1.0f, // bottom left	
   -1.0f,  1.0f, -1.0f, // top left		
   

	// right face 	 	
	1.0f, -1.0f, -1.0f, // bottom right
	1.0f, -1.0f,  1.0f, // bottom left
	1.0f,  1.0f, -1.0f, // top right
	1.0f,  1.0f, -1.0f, // top right
	1.0f, -1.0f,  1.0f, // bottom left
	1.0f,  1.0f,  1.0f, // top left	

	// front face   
	1.0f, -1.0f,  1.0f, // bottom right
   -1.0f, -1.0f,  1.0f, // bottom left
	1.0f,  1.0f,  1.0f, // top right
	1.0f,  1.0f,  1.0f, // top right
   -1.0f, -1.0f,  1.0f, // bottom left
   -1.0f,  1.0f,  1.0f, // top left	    

	// top face   
    1.0f,  1.0f,  1.0f, // bottom right
   -1.0f,  1.0f,  1.0f, // bottom left
    1.0f,  1.0f, -1.0f, // top right
	1.0f,  1.0f, -1.0f, // top right
   -1.0f,  1.0f,  1.0f, // bottom left
   -1.0f,  1.0f, -1.0f, // top left   
	 
	// bottom face   
	1.0f, -1.0f, -1.0f, // bottom right
   -1.0f, -1.0f, -1.0f, // bottom left
	1.0f, -1.0f,  1.0f, // top right
	1.0f, -1.0f,  1.0f, // top right
   -1.0f, -1.0f, -1.0f, // bottom left 		 
   -1.0f, -1.0f,  1.0f, // top left   
};

std::shared_ptr<ICubeLoader> ICubeLoader::create_cube_loader(){

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		return std::make_shared<OpenGL::OpenGLCubeLoader>();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		std::shared_ptr<ICubeLoader> cube_loader = nullptr;
		FatalError::fatal_error("Vulkan cube loader does not exist!.");
		return cube_loader;
	}

	FatalError::fatal_error("Unknown graphics API type.  Cannot return cube loader.");
	std::shared_ptr<ICubeLoader> cube_loader = nullptr;
	return cube_loader;
	
}
