#pragma once

//non-copyable
class VBO
{
public:
#pragma region Constructors, destructor, assign operators
	VBO()
	{
		glGenBuffers(1, &id);
	}

	VBO(const VBO&) = delete;
	VBO(VBO&& other) noexcept
	{
		auto tmp = id;
		id = other.id;
		other.id = tmp;
	}

	VBO& operator=(const VBO&) = delete;
	VBO& operator=(VBO&& other) noexcept
	{
		if(this != &other)
		{
			auto tmp = id;
			id = other.id;
			other.id = tmp;
		}

		return *this;
	}

	~VBO()
	{
		if(id != 0)
		{
			glDeleteBuffers(1, &id);
		}
	}
#pragma endregion

	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void bufferData(const void* vertices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW)
	{
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	}
	void bufferSubData(const void* vertices, GLsizeiptr size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
	}
	void setAttributesPointers(GLuint index, GLint size, GLenum type, GLsizei stride, const void* offset)
	{
		glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(index);
	}

private:
	GLuint id = 0;
};

