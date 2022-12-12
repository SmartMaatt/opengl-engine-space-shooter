#pragma once

//non-copyable
class VAO
{
public:
#pragma region Constructors, destructor, assign operators
	VAO()
	{
		glGenVertexArrays(1, &id);
	}
	
	VAO(const VAO&) = delete;
	VAO(VAO&& other) noexcept
	{
		auto tmp = id;
		id = other.id;
		other.id = tmp;
	}
	
	VAO& operator=(const VAO& other) = delete;
	VAO& operator=(VAO&& other) noexcept
	{
		if(this != &other)
		{
			auto tmp = id;
			id = other.id;
			other.id = tmp;
		}

		return *this;
	}

	~VAO()
	{
		if(id != -1)
		{
			glDeleteVertexArrays(1, &id);
		}
	}
#pragma endregion

	void bind()
	{
		glBindVertexArray(id);
	}
	void unbind()
	{
		glBindVertexArray(0);
	}

private:
	GLuint id = 0;
};

