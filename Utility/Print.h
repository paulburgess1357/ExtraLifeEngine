#pragma once
#include <iostream>
#include <string>

class Print{
	
public:

	template <typename T>
	static void print(T val){
		std::cout << val << std::endl;
	}
	
	static void print_separator(const bool space_above = false, const bool space_below = false){
		if(space_above){
			std::cout << std::endl;
		}
		
		std::cout << "================================" << std::endl;

		if(space_below){
			std::cout << std::endl;
		}
	}
	
};