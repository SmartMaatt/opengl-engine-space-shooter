#pragma once
#include "light.h"
#include "attenuation.h"

namespace Light
{
	class Spot : public Light
	{
	public:
		// Constructors / Destructor
		Spot(const glm::vec3& _position, const glm::vec3& color, float cutoff);
		Spot(const glm::vec3& _position, const glm::vec3& color, float _innerCutoff, float _outerCutoff);

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
			_attenuation.setAttenuationByRange(range);
		}
#pragma endregion
#pragma endregion

	private:
		// References
		Attenuation _attenuation;

		// Parameters
		glm::vec3 _position;
		float _range = 50;
		float _innerCutoff; // In deg
		float _outerCutoff; // In deg
	};
}