#pragma once

class EBO
{
public:
#pragma region Constructors, destructor, assign operators
	EBO()
	{
		glGenBuffers(1, &id);
	}

	EBO(const EBO&) = delete;
	EBO(EBO&& other) noexcept
	{
		auto tmp = id;
		id = other.id;
		other.id = tmp;
	}

	EBO& operator=(const EBO&) = delete;
	EBO& operator=(EBO&& other) noexcept
	{
		if(this != &other)
		{
			auto tmp = id;
			id = other.id;
			other.id = tmp;
		}

		return *this;
	}

	~EBO()
	{
		if(id != 0)
		{
			glDeleteBuffers(1, &id);
		}
	}
#pragma endregion

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
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
	GLuint id = 0;
};

