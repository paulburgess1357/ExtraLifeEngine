#pragma once
#include <vector>

template<typename T>
class Vector3D {

public:
	Vector3D(const size_t width, const size_t height, const size_t depth);
	T at(const size_t x, const size_t y, const size_t z) const;
	//void push_back(const T& value);
	
private:
	std::vector<T> m_data;
	
	size_t m_width{ 0 };
	size_t m_height{ 0 };
	size_t m_depth{ 0 };	
};

