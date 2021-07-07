#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class FatalError{
public:
	static void fatal_error(const std::string& error_string){		
		std::cerr << "Fatal Error: " << error_string << std::endl;
		std::cerr << "Enter any key to quit" << std::endl;
		glfwTerminate();
		exit(1);
	}
};