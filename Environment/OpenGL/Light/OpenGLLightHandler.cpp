#include "OpenGLLightHandler.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include "../../../ResourceManagement/LightResource.h"

OpenGL::OpenGLLightHandler::OpenGLLightHandler()
	:m_current_dirlight{ 0 },
	 m_current_pointlight{ 0 },
	 m_shader_program{ nullptr }{	
}

void OpenGL::OpenGLLightHandler::attach_directional_light(const std::string& dirlight_name){

	const std::string dirlight_shader_name = create_shader_variable_name("dirlight", m_current_dirlight);
	Print::print("Attaching Directional Light: " + dirlight_name + " (" + dirlight_shader_name + ")");
	Print::print("Active Dirlight Quantity: " + std::to_string(m_current_dirlight));

	m_directional_light_map[dirlight_name].first = dirlight_shader_name;
	m_directional_light_map[dirlight_name].second = LightResource::get_dirlight(dirlight_name);

	m_shader_program->set_uniform(dirlight_shader_name + ".direction", m_directional_light_map[dirlight_name].second->m_direction);
	m_shader_program->set_uniform("active_dirlight_qty", m_current_dirlight);

	m_current_dirlight++;
	
}

void OpenGL::OpenGLLightHandler::attach_point_light(const std::string& pointlight_name){

	const std::string pointlight_shader_name = create_shader_variable_name("pointlight", m_current_pointlight);
	Print::print("Attaching PointLight: " + pointlight_name + " (" + pointlight_shader_name + ")");
	Print::print("Active PointLight Quantity: " + std::to_string(m_current_pointlight));

	m_pointlight_map[pointlight_name].first = pointlight_shader_name;
	m_pointlight_map[pointlight_name].second = LightResource::get_pointlight(pointlight_name);

	m_shader_program->set_uniform(pointlight_shader_name + ".position", m_pointlight_map[pointlight_name].second->m_position);
	m_shader_program->set_uniform(pointlight_shader_name + ".constant", m_pointlight_map[pointlight_name].second->m_constant);
	m_shader_program->set_uniform(pointlight_shader_name + ".linear", m_pointlight_map[pointlight_name].second->m_linear);
	m_shader_program->set_uniform(pointlight_shader_name + ".quadratic", m_pointlight_map[pointlight_name].second->m_quadratic);

	m_shader_program->set_uniform("active_pointlight_qty", m_current_pointlight);

	m_current_pointlight++;
	
}

void OpenGL::OpenGLLightHandler::attach_scene_light(const std::string& scenelight_name){

	Print::print("Attaching Scene Light: " + scenelight_name);
	m_scene_light_pair.first = scenelight_name;
	m_scene_light_pair.second = LightResource::get_scenelight(scenelight_name);

	m_shader_program->set_uniform("scenelight.ambient", m_scene_light_pair.second->m_ambient);
	m_shader_program->set_uniform("scenelight.diffuse", m_scene_light_pair.second->m_diffuse);
	m_shader_program->set_uniform("scenelight.specular", m_scene_light_pair.second->m_specular);
	
}

std::string OpenGL::OpenGLLightHandler::create_shader_variable_name(const std::string& name, const unsigned index) {
	return name + "[" + std::to_string(index) + "]";
}

void OpenGL::OpenGLLightHandler::set_shader_program(IShaderProgram& shader_program){
	m_shader_program = &shader_program;
}
