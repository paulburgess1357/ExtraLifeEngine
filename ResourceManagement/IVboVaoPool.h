#pragma once
#include <memory>
#include <queue>
#include <utility>

class IVboVaoPool{
	
public:	
	virtual ~IVboVaoPool() = default;	
	virtual std::pair<unsigned int, unsigned int> get_resource() = 0;
	virtual void return_resource(const std::pair<unsigned int, unsigned int>& resource) = 0;
	static std::unique_ptr<IVboVaoPool> create_vbo_vao_pool();
			
protected:
	std::queue<std::pair<unsigned int, unsigned int>> m_vbo_vao_resources;

private:
	virtual void check_vbo_vao_value(const std::pair<unsigned int, unsigned int>& vbo_vao) = 0;
};
