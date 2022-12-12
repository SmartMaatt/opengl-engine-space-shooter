#pragma once

struct DeferredRenderer
{
	DeferredRenderer();
	DeferredRenderer(const DeferredRenderer&) = delete;
	DeferredRenderer(DeferredRenderer&&) noexcept;

	DeferredRenderer& operator=(const DeferredRenderer&) = delete;
	DeferredRenderer& operator=(DeferredRenderer&&) noexcept;

	FBO gBuffer;
	
	static constexpr uint32_t attachmentsCount = 3;
	Texture attachments[attachmentsCount];
};

