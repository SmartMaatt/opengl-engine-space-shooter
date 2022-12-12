#pragma once

class Shader
{
public:
	enum class Type
	{
		eVertex,
		eFragment,
		eGeometry
	};

	Shader() = default;
	Shader(const Shader&) = delete;
	Shader(Shader&&) noexcept;
	~Shader();

	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&&) noexcept;

	static Shader createShaderFromSourceCode(const std::string& sourceCode, Type type);
	static Shader createShaderFromFile(const std::string& filePath, Type type);

	GLuint getShaderID() const
	{
		return shaderID;
	}
	Type getType() const
	{
		return type;
	}

private:
	explicit Shader(Type type);

	static std::string loadShaderSourceCodeFromFile(const std::string& filePath);

	void setSourceCode(const std::string& sourceCode);
	void compile();

	GLuint shaderID{};
	Type type;
};

