#pragma once
#include "font.h"

class Text
{
	friend class Button;

public:
	// Constructors / Destructor
	Text(int32_t x, int32_t y, std::string text, const Font& font, const glm::vec3& color = { 0.0f, 1.0f, 0.0f });
	Text(const Text&) = delete;
	Text& operator=(const Text&) = delete;

	// Drawing
	void render(const ShaderProgram& shader);

	// Getters / Setters
	void setText(std::string newText);
	const std::string& getText() const;

	void setColor(const glm::vec3& newColor);
	const glm::vec3& getColor() const;

	void setPosition(const glm::vec2& newPosition);
	glm::vec2 getPosition() const;

private:
	void _setForNewText();

	int32_t _x, _y;
	int32_t _width, _height;

	glm::vec3 _position;
	std::string _text;
	const Font* _fontPtr;
	glm::vec3 _color;

	std::vector<VAO> _VAOs;
	std::vector<VBO> _VBOs;
	std::vector<EBO> _EBOs;
};

