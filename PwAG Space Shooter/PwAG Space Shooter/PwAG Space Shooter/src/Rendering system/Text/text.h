#pragma once
#include "font.h"

class Text
{
	friend class Button;
public:
	Text(int32_t x, int32_t y, std::string text, const Font& font, const glm::vec3& color = { 0.0f, 1.0f, 0.0f });
	Text(const Text&) = delete;
	Text& operator=(const Text&) = delete;

	void render(const ShaderProgram& shader);

	void setText(std::string newText);
	const std::string& getText() const;

	void setColor(const glm::vec3& newColor);
	const glm::vec3& getColor() const;

	void setPosition(const glm::vec2& newPosition);
	glm::vec2 getPosition() const;
private:
	void setForNewText();

	int32_t x, y;
	int32_t width, height;

	glm::vec3 position;
	std::string text;
	const Font* fontPtr;
	glm::vec3 color;

	std::vector<VAO> VAOs;
	std::vector<VBO> VBOs;
	std::vector<EBO> EBOs;
};

