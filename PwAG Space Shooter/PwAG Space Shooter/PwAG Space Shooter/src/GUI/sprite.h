#pragma once
#include "../SourceDep/stb_image.h"

class Sprite
{
public:
	// Constructors / Destructor
	Sprite(const std::string& path, int width, int height, int xCenter, int yCenter, bool alpha);
	~Sprite();

	// Drawing
	void draw();

private:
	// Initialization
	void _initShaderProgram();
	void _initMeshData();
	void _initTexture();

	// Shader
	const std::string& _spriteVertShader = "shaders/sprite.vert";
	const std::string& _spriteFragShader = "shaders/sprite.frag";
	ShaderProgram _spriteProgram;

	// Buffers
	unsigned int _VBO, _VAO, _EBO;
	unsigned int _texture;

	// Parameters
	const std::string& _path;
	int _width = 0;
	int _height = 0;
	int _xCenter = 0;
	int _yCenter = 0;
	bool _alpha = false;
};