#pragma once
#include "../SourceDep/stb_image.h"

class Sprite
{
public:
	Sprite(const std::string& path, int width, int height, int xCenter, int yCenter, bool alpha);
	~Sprite();

	void Draw();

private:

	void InitShaderProgram();
	void InitMeshData();
	void InitTexture();
	void InitSprite();

	const std::string& spriteVertShader = "Shaders/sprite.vert";
	const std::string& spriteFragShader = "Shaders/sprite.frag";
	ShaderProgram spriteProgram;

	unsigned int VBO, VAO, EBO;
	unsigned int texture;

	const std::string& path;
	int width = 0;
	int height = 0;
	int xCenter = 0;
	int yCenter = 0;
	bool alpha = false;
};