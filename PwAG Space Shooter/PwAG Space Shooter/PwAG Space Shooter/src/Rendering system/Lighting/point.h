#pragma once
#include "light.h"
#include "attenuation.h"
#include "../OpenGL Objects/fbo.h"

class SpaceLevel;

namespace Light
{
	class Point : public Light
	{
	public:
		// Constructors / Destructor
		Point(const glm::vec3& position, const glm::vec3& color);
		Point(const Point& light);

		// Getters / Setters
#pragma region Inline functions
#pragma region Getters
		const glm::vec3& getPosition() const
		{
			return _position;
		}

		const Attenuation& getAttenuation() const
		{
			return _attenuation;
		}

		float getRange() const
		{
			return _range;
		}

		const glm::mat4& getLightSpaceMatrix() const
		{
			return _lightSpaceMatrix[0];
		}
#pragma endregion

#pragma region Setters
		void setPosition(const glm::vec3& position)
		{
			_position = position;
		}

		void setAttenuation(const Attenuation& attenuation)
		{
			_attenuation = attenuation;
		}

		void setRange(float range)
		{
			_range = range;
		}

		void setAttenuationByRange(float range)
		{
			_range = range;
			_attenuation.setAttenuationByRange(_range);
		}
#pragma endregion
#pragma endregion

	private:
		// References
		FBO _fbo;
		Texture _depthMap;
		Attenuation _attenuation;

		// Parameters
		glm::vec3 _position;
		float _range = 15;
		std::array<glm::mat4, 6> _lightSpaceMatrix;
	};
}
