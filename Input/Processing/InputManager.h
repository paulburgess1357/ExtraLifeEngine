#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <utility>

template<typename T>
class InputManager {

public:
	static bool is_pressed(const T key_id) {
		const auto it = m_is_key_pressed_map.find(key_id);
		if (it != m_is_key_pressed_map.end()) {
			return it->second.first;
		}
		return false;
	}

	static bool is_initial_press(const T key_id) {
		const auto it = m_is_key_pressed_map.find(key_id);
		if (it != m_is_key_pressed_map.end()) {			
			const bool return_value = it->second.second;
			it->second.second = false;
			return return_value;
		}
		return false;
	}

	static void window_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		
		switch (action) {

		case GLFW_PRESS:
			InputManager::set_press(static_cast<T>(key));
			break;

		case GLFW_RELEASE:
			InputManager::set_release(static_cast<T>(key));
			break;

		default:
			break;
		}
	}

private:
	InputManager() = default;
	~InputManager() = default;

	static void set_press(const T key_id) {
		m_is_key_pressed_map[key_id].first = true;
		m_is_key_pressed_map[key_id].second = true;
	}

	static void set_release(const T key_id) {
		m_is_key_pressed_map[key_id].first = false;
	}

	// key_id; <current press, initial press>
	static std::unordered_map<T, std::pair<bool, bool>> m_is_key_pressed_map;

};

template <typename T>
std::unordered_map<T, std::pair<bool, bool>> InputManager<T>::m_is_key_pressed_map;
