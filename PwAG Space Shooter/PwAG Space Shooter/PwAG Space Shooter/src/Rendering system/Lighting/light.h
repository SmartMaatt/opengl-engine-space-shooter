#pragma once

namespace Light
{
	class Light
	{
	public:
		Light(const glm::vec3& color);

	#pragma region Inline functions
		const glm::vec3& getColor() const
		{
			return color;
		}
		const glm::vec3& getAmbient() const
		{
			return ambient;
		}
		const glm::vec3& getSpecular() const
		{
			return specular;
		}
		const glm::vec3& getDiffuse() const
		{
			return diffuse;
		}

		void setColor(const glm::vec3& color)
		{
			this->color = color;

			this->ambient = color * 0.05f;
			this->specular = color * 1.0f;
			this->diffuse = color * 0.8f;
		}
	#pragma endregion
	protected:
		glm::vec3 color;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
