#pragma once
#include "../Environment/Interfaces/Texture/ITexture.h"
#include <memory>
#include <string>
#include <unordered_map>

class TextureResource {

public:
	TextureResource() = default;
	~TextureResource();
	[[nodiscard]] ITexture* get(const std::string& texture_name);
	
	void load(const std::string& texture_name, const std::string& texture_path, const bool apply_gamma_correction, const bool flip_texture = false);
	void load_model_textures(const std::string& texture_path, const bool apply_gamma_correction, const bool flip_texture = false);
	void load_cubemap_textures(const std::string& cubemap_name, const std::string& cubemap_folder, const bool apply_gamma_correction, const bool flip_textures = false);
	
	void destroy(const std::string& texture_name);
	void destroy_all();
	
private:
	[[nodiscard]] bool is_loaded(const std::string& texture_name) const;
	std::unordered_map<std::string, std::unique_ptr<ITexture>> m_texture_cache;	
};
