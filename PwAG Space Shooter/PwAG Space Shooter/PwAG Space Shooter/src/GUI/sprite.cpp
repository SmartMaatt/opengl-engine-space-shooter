#include "pch.h"
#include "sprite.h"

/* --->>> Constructors / Destructor <<<--- */
Sprite::Sprite(const std::string& path, int width, int height, int xCenter, int yCenter, bool alpha) : _path(path)
{
	_width = width;
	_height = height;
	_xCenter = xCenter;
	_yCenter = Config::g_defaultHeight - yCenter;
	_alpha = alpha;

	_initShaderProgram();
	_initMeshData();
	_initTexture();
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}


/* --->>> Drawing <<<--- */
void Sprite::draw()
{
	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);
	_spriteProgram.useShader();

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glEnable(GL_DEPTH_TEST);
}


/* --->>> Initialization <<<--- */
void Sprite::_initShaderProgram()
{
	Shader spriteVert = Shader::createShaderFromFile(_spriteVertShader, Shader::Type::eVertex);
	Shader spriteFrag = Shader::createShaderFromFile(_spriteFragShader, Shader::Type::eFragment);

	_spriteProgram.attachShader(spriteVert);
	_spriteProgram.attachShader(spriteFrag);
	_spriteProgram.linkShaderProgram();
}

void Sprite::_initMeshData()
{
	float normXCenter = (float)_xCenter / (float)Config::g_defaultWidth;
	float normYCenter = (float)_yCenter / (float)Config::g_defaultHeight;

	float normWidth = (float)_width / (float)Config::g_defaultWidth;
	float normHeight = (float)_height / (float)Config::g_defaultHeight;

	float upperRightX = 2 * (normXCenter + (normWidth / 2)) - 1;
	float upperRightY = 2 * (normYCenter + (normHeight / 2)) - 1;

	float bottomRightX = 2 * (normXCenter + (normWidth / 2)) - 1;
	float bottomRightY = 2 * (normYCenter - (normHeight / 2)) - 1;

	float bottomLeftX = 2 * (normXCenter - (normWidth / 2)) - 1;
	float bottomLeftY = 2 * (normYCenter - (normHeight / 2)) - 1;

	float upperLeftX = 2 * (normXCenter - (normWidth / 2)) - 1;
	float upperLeftY = 2 * (normYCenter + (normHeight / 2)) - 1;

	float vertices[] = {
		// Positions						// Colors           // Texture coordinates
		upperRightX,  upperRightY,  0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,		// top right
		bottomRightX, bottomRightY, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,		// bottom right
		bottomLeftX,  bottomLeftY,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,		// bottom left
		upperLeftX,   upperLeftY,	0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f		// top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // First triangle
		1, 2, 3  // Second triangle
	};

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Sprite::_initTexture()
{
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if (_alpha)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Debug::LogError("Failed to load texture");
	}
	stbi_image_free(data);
}