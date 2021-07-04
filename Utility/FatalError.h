#pragma once
#include "../ResourceManagement/ShaderResource.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Tests/GraphicsTesting/Cube/CubeResource.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class FatalError{
public:
	static void fatal_error(const std::string& error_string){

		//ShaderResource::destroy_all();
		//TextureResource::destroy_all();
		//CubeResource::destroy_all();
		
		std::cerr << "Fatal Error: " << error_string << std::endl;
		std::cerr << "Enter any key to quit" << std::endl;
		glfwTerminate();
		exit(1);
	}
};