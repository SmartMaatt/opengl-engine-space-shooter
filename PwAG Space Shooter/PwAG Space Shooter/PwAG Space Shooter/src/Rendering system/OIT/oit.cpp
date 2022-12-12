#include "pch.h"
#include "oit.h"

OIT::OIT()
	: opaqueTex(Texture::createTexture_OIT_opaque()), depthTex(Texture::createTexture_OIT_depth()), accumTex(Texture::createTexture_OIT_accum()), revealTex(Texture::createTexture_OIT_reveal()),
	transparentDrawBuffers{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 }
{
	opaque.bind();
	opaque.setColorAttachment(opaqueTex, 0);
	opaque.setDepthAttachment(depthTex);
	opaque.unbind();

	transparent.bind();
	transparent.bind();
	transparent.setColorAttachment(accumTex, 0);
	transparent.setColorAttachment(revealTex, 1);
	transparent.setDepthAttachment(depthTex);
	transparent.drawBuffers(2, transparentDrawBuffers);
	transparent.unbind();
}