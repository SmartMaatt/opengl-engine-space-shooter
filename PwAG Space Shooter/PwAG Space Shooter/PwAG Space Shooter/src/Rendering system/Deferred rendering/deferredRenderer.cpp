#include "pch.h"
#include "deferredRenderer.h"

DeferredRenderer::DeferredRenderer()
	: attachments { Texture::createTextureForPositionBuffer(), Texture::createTextureForNormalBuffer(), Texture::createTextureForAlbedoBuffer() }
{
	gBuffer.bind();

	GLenum attachments[attachmentsCount];
	for(size_t i = 0; i < attachmentsCount; ++i)
	{
		gBuffer.setColorAttachment(this->attachments[i], i);
		attachments[i] = GL_COLOR_ATTACHMENT0 + i;
	}

	gBuffer.drawBuffers(attachmentsCount, attachments);
}

DeferredRenderer::DeferredRenderer(DeferredRenderer&& other) noexcept
	: gBuffer(std::move(other.gBuffer)), attachments { std::move(other.attachments[0]),std::move(other.attachments[1]) ,std::move(other.attachments[2]) }
{
}

DeferredRenderer& DeferredRenderer::operator=(DeferredRenderer&& other) noexcept
{
	if(this != &other)
	{
		gBuffer = std::move(other.gBuffer);
		for(int i = 0; i < attachmentsCount; ++i)
		{
			attachments[i] = std::move(other.attachments[i]);
		}
	}

	return *this;
}
