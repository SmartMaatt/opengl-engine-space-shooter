#pragma once

struct OIT
{
	OIT();

	FBO opaque, transparent;
	Texture opaqueTex, depthTex, accumTex, revealTex;

	GLenum transparentDrawBuffers[2];
};

