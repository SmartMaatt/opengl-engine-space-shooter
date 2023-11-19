#pragma once

namespace Light
{
	class Attenuation
	{
	public:
		// Constructors / Destructor
		Attenuation() = default;
		Attenuation(float constant, float linear, float quadratic);

		// Getters / Setters
		void setAttenuationByRange(float _range);

#pragma region Inline functions
		float getConstant() const
		{
			return _constant;
		}

		float getLinear() const
		{
			return _linear;
		}

		float getQuadratic() const
		{
			return _quadratic;
		}

		void setConstant(float constant)
		{
			_constant = constant;
		}

		void setLinear(float linear)
		{
			_linear = linear;
		}

		void setQuadratic(float quadratic)
		{
			_quadratic = quadratic;
		}
#pragma endregion

	private:
		// Parameters
		float _constant = 1.0f;
		float _linear = 0.09f;
		float _quadratic = 0.032f;
	};
}
