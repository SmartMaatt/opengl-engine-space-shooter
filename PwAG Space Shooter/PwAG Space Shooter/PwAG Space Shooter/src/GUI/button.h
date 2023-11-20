#pragma once
#include "../Rendering system/Text/text.h"

class Button
{
public:
	// Constructors / Destructor
	Button(const std::string& text, const glm::vec2& position, const glm::vec3& color);

	// Update
	void update(const Mouse& mouse);

	// Drawing
	void draw();

	// Getters / Setters
	void setEnabled(bool enabled);
	bool isEnabled() const;

	void setPosition(const glm::vec2& position);
	const glm::vec2& getPosition() const;

	void setColor(const glm::vec3& color);
	const glm::vec3& getColor() const;

	void setText(const std::string& text);
	const std::string& getText() const;

	void setAction(std::function<void(void)> action);

private:
	// Parameters
	glm::vec2 _position{};
	glm::vec2 _size{};
	glm::vec3 _color{};
	bool _enabled = true;

	// Rendering
	const ShaderProgram& _shaderProgram;
	Text _text;

	// Actions
	std::function<void(void)> _action =
		[]()
	{};
};