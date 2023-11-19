#include "pch.h"
#include "sprite.h"

Sprite::Sprite(const std::string& path, int width, int height, int xCenter, int yCenter, bool alpha)
	: path(path)
{
	this->width = width;
	this->height = height;
	this->xCenter = xCenter;
	this->yCenter = Config::g_defaultHeight - yCenter;
	this->alpha = alpha;

	InitShaderProgram();
	InitMeshData();
	InitTexture();
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Sprite::InitShaderProgram()
{
	Shader spriteVert = Shader::createShaderFromFile(spriteVertShader, Shader::Type::eVertex);
	Shader spriteFrag = Shader::createShaderFromFile(spriteFragShader, Shader::Type::eFragment);

	spriteProgram.attachShader(spriteVert);
	spriteProgram.attachShader(spriteFrag);
	spriteProgram.linkShaderProgram();
}

void Sprite::InitMeshData()
{
	float normXCenter = (float)xCenter / (float)Config::g_defaultWidth;
	float normYCenter = (float)yCenter / (float)Config::g_defaultHeight;

	float normWidth = (float)width / (float)Config::g_defaultWidth;
	float normHeight = (float)height / (float)Config::g_defaultHeight;

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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

void Sprite::InitTexture()
{
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load(this->path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alpha)
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

void Sprite::Draw()
{
	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	spriteProgram.useShader();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glEnable(GL_DEPTH_TEST);
}