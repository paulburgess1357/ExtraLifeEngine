#pragma once
#include "ICommand.h"
#include <glad/glad.h>

namespace OpenGL{
	
	class OpenGLWireFrame : public ICommand {

	public:
		OpenGLWireFrame()
			:m_wireframe_enabled(false) {
		}

		void execute() override {
			if (m_wireframe_enabled) {
				m_wireframe_enabled = false;
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glEnable(GL_CULL_FACE);
			} else {
				m_wireframe_enabled = true;
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDisable(GL_CULL_FACE);
			}

		}
	private:
		bool m_wireframe_enabled;

	};
	
} // namespace OpenGL
