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

	// Constructors / Destructor
	Shader() = default;
	Shader(const Shader&) = delete;
	Shader(Shader&&) noexcept;
	~Shader();

	// Operators
	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&&) noexcept;

	// Initialization
	static Shader createShaderFromSourceCode(const std::string& sourceCode, Type type);
	static Shader createShaderFromFile(const std::string& filePath, Type type);

	// Getters
	GLuint getShaderID() const
	{
		return _shaderID;
	}

	Type getType() const
	{
		return _type;
	}

private:
	explicit Shader(Type type);
	static std::string _loadShaderSourceCodeFromFile(const std::string& filePath);

	void _setSourceCode(const std::string& sourceCode);
	void _compile();

	GLuint _shaderID{};
	Type _type;
};

