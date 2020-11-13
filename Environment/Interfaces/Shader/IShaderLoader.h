#pragma once
#include <string>
#include <utility>

class IShaderLoader{
	
public:
	IShaderLoader(const std::string& shader_name)
		:m_shader_name(shader_name){		
	};
	virtual ~IShaderLoader() = default;
	virtual std::pair<std::string, std::string> load() const = 0;
	std::string get_shader_name() const{
		return m_shader_name;
	}
	
private:
	std::string m_shader_name;
	
};
