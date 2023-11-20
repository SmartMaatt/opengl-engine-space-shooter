#include "pch.h"
#include "text.h"

/* --->>> Constructors / Destructor <<<--- */
Text::Text(int32_t x, int32_t y, std::string text, const Font& font, const glm::vec3& color) :
	_x(x), _y(y), _text(std::move(text)), _fontPtr(&font), _color(color)
{
	_setForNewText();
}

/* --->>> Drawing <<<--- */
void Text::render(const ShaderProgram& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _fontPtr->atlasTextureID);
	shader.setVec3f("textColor", _color);

	for (auto i = 0; i < _text.size(); ++i)
	{
		_VAOs[i].bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}


/* --->>> Setters <<<--- */
void Text::setText(std::string newText)
{
	_text = std::move(newText);
	_setForNewText();
}

const std::string& Text::getText() const
{
	return _text;
}

void Text::setColor(const glm::vec3& newColor)
{
	_color = newColor;
}

const glm::vec3& Text::getColor() const
{
	return _color;
}

void Text::setPosition(const glm::vec2& newPosition)
{
	_x = newPosition.x;
	_y = newPosition.y;

	_setForNewText();
}

glm::vec2 Text::getPosition() const
{
	return glm::vec2(_x, _y);
}

void Text::_setForNewText()
{
	_VBOs.clear();
	_VAOs.clear();

	_VAOs.reserve(_text.size());
	_VBOs.reserve(_text.size());

	float xPos = static_cast<float>(_x);
	float yPos = static_cast<float>(_y);

	for (const auto charInText : _text)
	{
		const Font::Character& character = _fontPtr->characters.at(charInText);

		float width = static_cast<float>(character.size.x);
		float height = static_cast<float>(character.size.y);

		_width += character.size.x + character.bearing.x;
		_height = std::max(_height, static_cast<int32_t>(height));
	}

	for (const auto charInText : _text)
	{
		const Font::Character& character = _fontPtr->characters.at(charInText);

		float width = static_cast<float>(character.size.x);
		float height = static_cast<float>(character.size.y);

		float x1 = xPos + character.bearing.x;
		float y1 = yPos + character.bearing.y - _height;

		float x2 = x1 + width;
		float y2 = y1 - height;

		float vertices[] = {
			x1,			y1,				character.atlasOffset.x / _fontPtr->atlasSize.x,											0,
			x2,			y1,				character.atlasOffset.x / _fontPtr->atlasSize.x + width / _fontPtr->atlasSize.x,			0,
			x1,			y2,				character.atlasOffset.x / _fontPtr->atlasSize.x,											height / _fontPtr->atlasSize.y,

			//x2,			y1,				character.atlasOffset.x / fontPtr->atlasSize.x + width / fontPtr->atlasSize.x,			0,
			//x1,			y2,				character.atlasOffset.x / fontPtr->atlasSize.x,											height / fontPtr->atlasSize.y,
			x2,			y2,				character.atlasOffset.x / _fontPtr->atlasSize.x + width / _fontPtr->atlasSize.x,			height / _fontPtr->atlasSize.y
		};

		unsigned int indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		_VAOs.emplace_back();
		_VAOs.back().bind();

		_VBOs.emplace_back();
		_VBOs.back().bind();

		_VBOs.back().bufferData(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);

		_EBOs.emplace_back();
		_EBOs.back().bind();

		_EBOs.back().bufferData(indices, sizeof(indices), GL_DYNAMIC_DRAW);
		_VBOs.back().setAttributesPointers(0, 4, GL_FLOAT, 4 * sizeof(float), nullptr);

		_VBOs.back().unbind();
		_VAOs.back().unbind();

		xPos += character.advance.x;
		yPos += character.advance.y;

		_width = xPos - _x;
	}
}
