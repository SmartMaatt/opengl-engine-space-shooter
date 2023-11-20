#include "pch.h"
#include "skybox.h"

float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};


/* --->>> Constructors / Destructor <<<--- */
Skybox::Skybox(std::string facesCubemap[6])
{
	InitializeShader();
	InitializeBuffers();
	InitializeTextures(facesCubemap);
}

Skybox::~Skybox()
{
	delete this->_shaderProgram;
	glDeleteBuffers(1, &_skyboxVBO);
	glDeleteBuffers(1, &_skyboxEBO);
	glDeleteTextures(1, &_cubemapTexture);
	glDeleteVertexArrays(1, &_skyboxVAO);
}


/* --->>> Initialization <<<--- */
void Skybox::InitializeShader()
{
	_fragShader = Shader::createShaderFromFile("shaders/skybox.frag", Shader::Type::eFragment);
	_vertShader = Shader::createShaderFromFile("shaders/skybox.vert", Shader::Type::eVertex);

	_shaderProgram = new ShaderProgram();
	_shaderProgram->attachShader(_fragShader);
	_shaderProgram->attachShader(_vertShader);
	_shaderProgram->linkShaderProgram();

	_shaderProgram->useShader();
	_shaderProgram->setInt("skybox", 0);
}

void Skybox::InitializeBuffers()
{
	glGenVertexArrays(1, &_skyboxVAO);
	glGenBuffers(1, &_skyboxVBO);
	glGenBuffers(1, &_skyboxEBO);

	glBindVertexArray(_skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::InitializeTextures(std::string facesCubemap[6])
{
	glGenTextures(1, &_cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			Debug::LogError("Failed to load texture: " + facesCubemap[i]);
			stbi_image_free(data);
		}
	}
}


/* --->>> Drawing <<<--- */
void Skybox::draw(glm::vec3 _position, glm::vec3 orientation, glm::vec3 up)
{
	// Since the cubemap will always have a depth of 1.0, we need that equal sign so it doesn't get discarded
	glDepthFunc(GL_LEQUAL);

	_shaderProgram->useShader();
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
	// The last row and column affect the translation of the skybox (which we don't want to affect)
	view = glm::mat4(glm::mat3(glm::lookAt(_position, _position + orientation, up)));
	projection = glm::perspective(glm::radians(45.0f), (float)Config::g_defaultWidth / (float)Config::g_defaultHeight, 0.1f, 100.0f);

	_shaderProgram->setMat4("view", view);
	_shaderProgram->setMat4("projection", projection);

	// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
	// where an object is present (a depth of 1.0f will always fail against any object's depth value)
	glBindVertexArray(_skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Switch back to the normal depth function
	glDepthFunc(GL_LESS);
}
