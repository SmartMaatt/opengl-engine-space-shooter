#pragma once

class EBO
{
public:
#pragma region Constructors, destructor, assign operators
	EBO()
	{
		glGenBuffers(1, &_id);
	}

	EBO(const EBO&) = delete;
	EBO(EBO&& other) noexcept
	{
		auto tmp = _id;
		_id = other._id;
		other._id = tmp;
	}

	EBO& operator=(const EBO&) = delete;
	EBO& operator=(EBO&& other) noexcept
	{
		if (this != &other)
		{
			auto tmp = _id;
			_id = other._id;
			other._id = tmp;
		}

		return *this;
	}

	~EBO()
	{
		if (_id != 0)
		{
			glDeleteBuffers(1, &_id);
		}
	}
#pragma endregion

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}
	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void bufferData(GLuint indices[], GLsizei size, GLenum usage = GL_STATIC_DRAW)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
	}

	void drawElements(GLenum mode, int size, GLenum type, const void* offset = nullptr)
	{
		glDrawElements(mode, size, type, offset);
	}

private:
	GLuint _id = 0;
};

