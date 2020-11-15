#pragma once

struct TextureLoadingData {
	
	int m_width { 0 };
	int m_height { 0 };
	int m_components { 0 };
	void* m_image_data = nullptr;
	
};