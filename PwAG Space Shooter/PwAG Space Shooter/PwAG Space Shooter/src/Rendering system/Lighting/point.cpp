#include "pch.h"
#include "point.h"
#include "../../Game Objects/spaceLevel.h"

Light::Point::Point(const glm::vec3& position, const glm::vec3& color) :
Light(color), position(position), fbo(), depthMap(Texture::createDepthTexture())
{
	setColor(color);
	attenuation.setAttenuationByRange(range);

	fbo.bind();
	fbo.setDepthAttachment(this->depthMap);
	fbo.drawBufferNone();
	fbo.readBufferNone();
	fbo.unbind();

	glm::mat4 lightProjection =	glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	this->position = position;

	lightSpaceMatrix =
	{
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
	};
}

Light::Point::Point(const Point& light) :
Light(light.getColor()), position(light.getPosition()), fbo(), depthMap(Texture::createDepthTexture())
{
	setColor(color);
	attenuation.setAttenuationByRange(range);

	fbo.bind();
	fbo.setDepthAttachment(this->depthMap);
	fbo.drawBufferNone();
	fbo.readBufferNone();
	fbo.unbind();

	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	this->position = position;

	lightSpaceMatrix =
	{
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(this->position, this->position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
	};
}