#pragma once
#include "../Texture/texture.h"

class FBO
{
public:
	enum class Type
	{
		eColor,
		eDepth,
		eStencil,
		eDepthStencil
	};

	FBO()
	{
		glGenFramebuffers(1, &_id);
	}

	FBO(const FBO&) = delete;
	FBO(FBO&& other) noexcept
	{
		_id = other._id;
		other._id = 0;
	}

	~FBO()
	{
		if (_id != 0)
		{
			glDeleteFramebuffers(1, &_id);
			_id = 0;
		}
	}

	FBO& operator=(const FBO&) = delete;
	FBO& operator=(FBO&& other) noexcept
	{
		if (this != &other)
		{
			_id = other._id;
			other._id = 0;
		}

		return *this;
	}

	bool checkStatus() const
	{
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}

	void bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _id);
	}

	void bindRead() const
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _id);
	}

	void bindDraw() const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _id);
	}

	void unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void unbindRead() const
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	void unbindDraw() const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void drawBuffers(GLsizei count, GLenum attachments[])
	{
		glDrawBuffers(count, attachments);
	}

	void drawBufferNone() const
	{
		glDrawBuffer(GL_NONE);
	}

	void readBufferNone() const
	{
		glReadBuffer(GL_NONE);
	}

	void setColorAttachment(const Texture& texture, uint32_t attachment) const
	{
		assert(attachment >= 0 && attachment <= 31);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, texture._texture, 0);
	}

	void setDepthAttachment(const Texture& texture) const
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture._texture, 0);
	}

	void setStencilAttachment(const Texture& texture) const
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture._texture, 0);
	}

	void setDepthStencilAttachment(const Texture& texture) const
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture._texture, 0);
	}

	void blit(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

private:
	GLuint _id{};
};

