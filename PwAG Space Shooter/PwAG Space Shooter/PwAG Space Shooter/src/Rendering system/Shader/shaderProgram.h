#pragma once
#include "shader.h"

// 1. Create shader program.
// 2. Create all necessary shaders (at least vertex and fragment).
// 3. Attach all created shaders to shader program.
// 4. Link shader program.
class ShaderProgram
{
public:
	ShaderProgram() = default;
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram(ShaderProgram&&) noexcept;
	~ShaderProgram();

	ShaderProgram& operator=(const ShaderProgram&) = delete;
	ShaderProgram& operator=(ShaderProgram&&) noexcept;

	void attachShader(const Shader& shader);
	bool linkShaderProgram();

	void useShader() const
	{
		glUseProgram(shaderProgram);
	}

	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2f(const std::string& name, const glm::vec2& vector) const;
	void setVec3f(const std::string& name, const glm::vec3& vector) const;
	void setVec4f(const std::string& name, const glm::vec4& vector) const;
	void setMat4(const std::string& name, const glm::mat4& matrix) const;
private:
	GLint getUniformLocation(const std::string& name) const;

	GLuint shaderProgram = glCreateProgram();
	mutable std::unordered_map<std::string, GLint> uniformLocation;
};

