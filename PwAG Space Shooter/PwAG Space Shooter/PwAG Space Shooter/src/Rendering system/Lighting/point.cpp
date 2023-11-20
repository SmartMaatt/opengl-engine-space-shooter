#include "pch.h"
#include "point.h"
#include "../Rendering system/Space level/spaceLevel.h"

/* --->>> Constructors / Destructor <<<--- */
Light::Point::Point(const glm::vec3& position, const glm::vec3& color) :
	Light(color), _position(position), _fbo(), _depthMap(Texture::createDepthTexture())
{
	setColor(color);
	_attenuation.setAttenuationByRange(_range);

	_fbo.bind();
	_fbo.setDepthAttachment(_depthMap);
	_fbo.drawBufferNone();
	_fbo.readBufferNone();
	_fbo.unbind();

	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	_position = position;

	_lightSpaceMatrix =
	{
		lightProjection * glm::lookAt(_position, _position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
	};
}

Light::Point::Point(const Point& light) :
	Light(light.getColor()), _position(light.getPosition()), _fbo(), _depthMap(Texture::createDepthTexture())
{
	setColor(_color);
	_attenuation.setAttenuationByRange(_range);

	_fbo.bind();
	_fbo.setDepthAttachment(_depthMap);
	_fbo.drawBufferNone();
	_fbo.readBufferNone();
	_fbo.unbind();

	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	_position = light.getPosition();

	_lightSpaceMatrix =
	{
		lightProjection * glm::lookAt(_position, _position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		lightProjection * glm::lookAt(_position, _position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
	};
}