#pragma once
#include "../Environment/Interfaces/Texture/ITexture.h"
#include <memory>
#include <string>
#include <unordered_map>

class TextureResource {

public:
	static std::shared_ptr<ITexture> load(const std::string& texture_name, const std::string& texture_path, const bool flip_texture);
	static std::shared_ptr<ITexture> get(const std::string& texture_name);
	static void destroy(const std::string& texture_name);
	static void destroy_all();

private:
	TextureResource() = default;
	static bool is_loaded(const std::string& texture_name);
	static std::unordered_map<std::string, std::shared_ptr<ITexture>> m_texture_cache;
	
};


