#include "pch.h"

class Skybox
{
public:
	// Constructors / Destructor
	Skybox(std::string facesCubemap[6]);
	~Skybox();

	// Drawing
	void draw(glm::vec3 _position, glm::vec3 orientation, glm::vec3 up);

private:
	// Initialization
	void InitializeShader();
	void InitializeBuffers();
	void InitializeTextures(std::string facesCubemap[6]);

	ShaderProgram* _shaderProgram;
	Shader _vertShader;
	Shader _fragShader;

	GLuint _skyboxVAO, _skyboxVBO, _skyboxEBO;
	GLuint _cubemapTexture;
};

