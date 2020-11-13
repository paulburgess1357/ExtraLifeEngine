#pragma once
#include "../../Interfaces/Shader/IShaderProgram.h"

namespace OpenGL{

	class OpenGLShaderProgram : public IShaderProgram{
		
	public:		
		OpenGLShaderProgram(const std::string& shader_name, const unsigned int handle);
		
		void bind() const override;
		void unbind() const override;
		void destroy() const override;

		// Single Value Uniforms
		void set_uniform(const std::string& uniform_name, const int value) override;
		void set_uniform(const std::string& uniform_name, const float value) override;

		// Vector Uniforms
		void set_uniform(const std::string& uniform_name, const glm::vec2& value) override;
		void set_uniform(const std::string& uniform_name, const glm::vec3& value) override;
		void set_uniform(const std::string& uniform_name, const glm::vec4& value) override;

		// Matrix Uniforms		
		void set_uniform(const std::string& uniform_name, const glm::mat3& value) override;
		void set_uniform(const std::string& uniform_name, const glm::mat4& value) override;

	private:
		int get_uniform(const std::string& uniform_name) override;
		
	};
	
} // namespace OpenGL



