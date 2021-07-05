#pragma once
#include "string"

struct TextureLoadingData {	
	int m_width { 0 };
	int m_height { 0 };
	int m_components { 0 };
	void* m_image_data = nullptr;
	std::string m_texture_name = "No texture name assigned";
};