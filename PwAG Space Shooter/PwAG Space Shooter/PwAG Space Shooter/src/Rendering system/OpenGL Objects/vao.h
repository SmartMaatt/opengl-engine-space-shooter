#pragma once

//non-copyable
class VAO
{
public:
#pragma region Constructors, destructor, assign operators
	VAO()
	{
		glGenVertexArrays(1, &_id);
	}

	VAO(const VAO&) = delete;
	VAO(VAO&& other) noexcept
	{
		auto tmp = _id;
		_id = other._id;
		other._id = tmp;
	}

	VAO& operator=(const VAO& other) = delete;
	VAO& operator=(VAO&& other) noexcept
	{
		if (this != &other)
		{
			auto tmp = _id;
			_id = other._id;
			other._id = tmp;
		}

		return *this;
	}

	~VAO()
	{
		if (_id != -1)
		{
			glDeleteVertexArrays(1, &_id);
		}
	}
#pragma endregion

	void bind()
	{
		glBindVertexArray(_id);
	}

	void unbind()
	{
		glBindVertexArray(0);
	}

private:
	GLuint _id = 0;
};