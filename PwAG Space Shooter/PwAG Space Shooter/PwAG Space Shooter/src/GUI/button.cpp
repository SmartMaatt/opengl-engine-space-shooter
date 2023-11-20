#include "pch.h"
#include "button.h"

/* --->>> Constructors / Destructor <<<--- */
Button::Button(const std::string& text, const glm::vec2& position, const glm::vec3& color)
	: _text(position.x, Config::g_defaultHeight - position.y, text, ResourceManager::getInstance().getFont("default")), _shaderProgram(ResourceManager::getInstance().getShader("text")), _position(position), _color(color)
{
	_size = { _text._width, _text._height };
}


/* --->>> Update <<<--- */
void Button::update(const Mouse& mouse)
{
	if (_enabled &&
		mouse.posX > _position.x && mouse.posX < _position.x + _size.x &&
		mouse.posY > _position.y && mouse.posY < _position.y + _size.y)
	{
		_text._color = _color * 1.5f;
		if (mouse.buttonState[static_cast<int>(Mouse::Button::eLeft)])
		{
			_action();
		}
	}
	else
	{
		_text._color = _color;
	}
}


/* --->>> Drawing <<<--- */
void Button::draw()
{
#ifndef DIST
	_shaderProgram.useShader();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Config::g_defaultWidth), 0.0f, static_cast<float>(Config::g_defaultHeight));
	_shaderProgram.setMat4("MVP", projection);
	_text.render(_shaderProgram);
#endif
}


/* --->>> Getters / Setters <<<--- */
void Button::setEnabled(bool enabled)
{
	_enabled = enabled;
}

bool Button::isEnabled() const
{
	return _enabled;
}

void Button::setPosition(const glm::vec2& position)
{
	_position = position;
	_text.setPosition(position);
}

const glm::vec2& Button::getPosition() const
{
	return _position;
}

void Button::setColor(const glm::vec3& color)
{
	_color = color;
	_text.setColor(color);
}

const glm::vec3& Button::getColor() const
{
	return _color;
}

void Button::setText(const std::string& text)
{
	_text.setText(text);
	_size = { _text._width, _text._height };
}

const std::string& Button::getText() const
{
	return _text.getText();
}

void Button::setAction(std::function<void(void)> action)
{
	_action = std::move(action);
}
