#pragma once
#include "../Rendering system/Text/text.h"

class Button
{
public:
	Button(const std::string& text, const glm::vec2& position, const glm::vec3& color);

	void setEnabled(bool enabled);
	bool isEnabled() const;

	void setPosition(const glm::vec2& position);
	const glm::vec2& getPosition() const;

	void setColor(const glm::vec3& color);
	const glm::vec3& getColor() const;

	void setText(const std::string& text);
	const std::string& getText() const;

	void update(const Mouse& mouse);
	void draw();

	void setAction(std::function<void(void)> action);

private:
	glm::vec2 position {};
	glm::vec2 size {};
	glm::vec3 color {};

	bool enabled = true;

	const ShaderProgram& shaderRef;
	Text text;

	std::function<void(void)> action =
		[]()
	{};
};

