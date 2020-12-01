#pragma once
#include "../ECS/Components/Lights/PointLight.h"
#include "../ECS/Components/Lights/SceneLight.h"
#include "../ECS/Components/Lights/DirectionalLight.h"
#include <memory>
#include <string>
#include <unordered_map>

class LightResource{

public:
	static std::shared_ptr<DirectionalLight> load(const std::string& light_name, const DirectionalLight& dirlight);
	static std::shared_ptr<PointLight> load(const std::string& light_name, const PointLight& pointlight);
	static std::shared_ptr<SceneLight> load(const std::string& light_name, const SceneLight& scenelight);

	static std::shared_ptr<DirectionalLight> get_dirlight(const std::string& light_name);
	static std::shared_ptr<PointLight> get_pointlight(const std::string& light_name);
	static std::shared_ptr<SceneLight> get_scenelight(const std::string& light_name);

	static void destroy_dirlight(const std::string& light_name);
	static void destroy_pointlight(const std::string& light_name);
	static void destroy_scenelight(const std::string& light_name);

	static void destroy_all();

private:
	LightResource() = default;
	static bool is_dirlight_loaded(const std::string& light_name);
	static bool is_pointlight_loaded(const std::string& light_name);
	static bool is_scenelight_loaded(const std::string& light_name);

	static void check_point_light(const PointLight& pointlight);

	static std::unordered_map<std::string, std::shared_ptr<DirectionalLight>> m_dirlight_cache;
	static std::unordered_map<std::string, std::shared_ptr<PointLight>> m_pointlight_cache;
	static std::unordered_map<std::string, std::shared_ptr<SceneLight>> m_scenelight_cache;
};

