#pragma once
#include <memory>
#include <queue>
#include <utility>

class VboVaoPool{
	
public:	
	virtual ~VboVaoPool() = default;
	virtual std::shared_ptr<VboVaoPool> get_instance() = 0;
	virtual std::pair<unsigned int, unsigned int> get_resource() = 0;
	virtual std::pair<int, int> return_resource(std::pair<unsigned int, unsigned int> resource) = 0;
		
protected:
	static std::shared_ptr<VboVaoPool> m_pool_instance;
	std::queue<std::pair<unsigned int, unsigned int>> m_vbo_vao_resources;
	
};