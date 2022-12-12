#include "pch.h"
#include "button.h"

Button::Button(const std::string& text, const glm::vec2& position, const glm::vec3& color)
	: text(position.x, Config::g_defaultHeight - position.y, text, ResourceManager::getInstance().getFont("default")), shaderRef(ResourceManager::getInstance().getShader("text")), position(position), color(color)
{
	this->size = { this->text.width, this->text.height };
}

void Button::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool Button::isEnabled() const
{
	return this->enabled;
}

void Button::setPosition(const glm::vec2& position)
{
	this->position = position;
	this->text.setPosition(position);
}

const glm::vec2& Button::getPosition() const
{
	return this->position;
}

void Button::setColor(const glm::vec3& color)
{
	this->color = color;
	this->text.setColor(color);
}

const glm::vec3& Button::getColor() const
{
	return this->color;
}

void Button::setText(const std::string& text)
{
	this->text.setText(text);
	this->size = { this->text.width, this->text.height };
}

const std::string& Button::getText() const
{
	return this->text.getText();
}

void Button::update(const Mouse& mouse)
{
	if(enabled && 
	   mouse.posX > this->position.x
	   &&
	   mouse.posX < this->position.x + this->size.x

	   &&

	   mouse.posY > this->position.y
	   &&
	   mouse.posY < this->position.y + this->size.y 
	   )
	{
		this->text.color = this->color * 1.5f;
		if(mouse.buttonState[static_cast<int>(Mouse::Button::eLeft)])
		{
			action();
		}
	}
	else
	{
		this->text.color = this->color;
	}
}

void Button::draw()
{
	this->text.render(this->shaderRef);
}

void Button::setAction(std::function<void(void)> action)
{
	this->action = std::move(action);
}
