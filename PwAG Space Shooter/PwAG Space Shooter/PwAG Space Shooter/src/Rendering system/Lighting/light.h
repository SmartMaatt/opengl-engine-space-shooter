#pragma once

namespace Light
{
	class Light
	{
	public:
		// Constructors / Destructor
		Light(const glm::vec3& color);

		// Inline functions
#pragma region Inline functions
		const glm::vec3& getColor() const
		{
			return _color;
		}

		const glm::vec3& getAmbient() const
		{
			return _ambient;
		}

		const glm::vec3& getSpecular() const
		{
			return _specular;
		}

		const glm::vec3& getDiffuse() const
		{
			return _diffuse;
		}

		void setColor(const glm::vec3& color)
		{
			_color = color;
			_ambient = color * 0.05f;
			_specular = color * 1.0f;
			_diffuse = color * 0.8f;
		}
#pragma endregion

	protected:
		// Parameters
		glm::vec3 _color;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
	};
}
