#pragma once
#include "../ECS/Components/Lights/PointLight.h"
#include "../ECS/Components/Lights/SceneLight.h"
#include "../ECS/Components/Lights/DirectionalLight.h"
#include <memory>
#include <string>
#include <unordered_map>

class LightResource{

public:
	LightResource() = default;
	~LightResource();
	void load(const DirectionalLight& dirlight);
	void load(const PointLight& pointlight);
	void load(const SceneLight& scenelight);

	[[nodiscard]] DirectionalLight* get_dirlight(const std::string& light_name);
	[[nodiscard]] PointLight* get_pointlight(const std::string& light_name);
	[[nodiscard]] SceneLight* get_scenelight(const std::string& light_name);

	void destroy_dirlight(const std::string& light_name);
	void destroy_pointlight(const std::string& light_name);
	void destroy_scenelight(const std::string& light_name);
	void destroy_all();

private:	
	[[nodiscard]] bool is_dirlight_loaded(const std::string& light_name) const;
	[[nodiscard]] bool is_pointlight_loaded(const std::string& light_name) const;
	[[nodiscard]] bool is_scenelight_loaded(const std::string& light_name) const;
	static void check_point_light(const PointLight& pointlight);

	std::unordered_map<std::string, std::unique_ptr<DirectionalLight>> m_dirlight_cache;
	std::unordered_map<std::string, std::unique_ptr<PointLight>> m_pointlight_cache;
	std::unordered_map<std::string, std::unique_ptr<SceneLight>> m_scenelight_cache;
};
