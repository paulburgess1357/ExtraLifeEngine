#pragma once
#include "../../Interfaces/Window/IWindow.h"
#include "../../Interfaces/Window/IWindowCreator.h"

namespace OpenGL {

	class OpenGLWindowCreator : public IWindowCreator {

	public:
		OpenGLWindowCreator(const int width, const int height, const bool mouse_enabled, const bool is_resizeable);
		~OpenGLWindowCreator() = default;

		[[nodiscard]] std::shared_ptr<IWindow> create_glfw_window() override;

	private:
		void init_glfw_hints() const;
		void init_glad() const;
		void init_opengl_settings() const;

		int m_width;
		int m_height;
		bool m_is_resizeable;
		bool m_mouse_enabled;
		static std::shared_ptr<IWindow> m_opengl_window;

	};

} // namespace OpenGL