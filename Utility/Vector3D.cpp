#include "Vector3D.h"

template <typename T>
Vector3D<T>::Vector3D(const size_t width, const size_t height, const size_t depth)
	:m_width{ width },
	m_height{ height },
	m_depth{ depth }{
	m_data(width* height, depth);
}

template <typename T>
T Vector3D<T>::at(const size_t x, const size_t y, const size_t z) const{
	return m_data[x * m_height * m_depth + y * m_depth + z];
}

//template <typename T>
//void Vector3D<T>::push_back(const T& value){
//	m_data.push_back(value);
//}
