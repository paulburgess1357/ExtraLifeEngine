#pragma once
#include <string>
#include <utility>

class IShaderLoader{
	
public:
	virtual ~IShaderLoader() = default;
	[[nodiscard]] virtual std::pair<std::string, std::string> load() const = 0;
	
};
