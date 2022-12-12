#include "pch.h"
#include "font.h"

Font::Font(const std::string& fontFilePath, uint32_t size)
{
	FT_Library freetype;
	if (FT_Init_FreeType(&freetype))
	{
		std::cout << "Freetype initialization failed!" << std::endl;

		return;
	}

	FT_Face face;
	if (FT_New_Face(freetype, fontFilePath.c_str(), 0, &face))
	{
		std::cout << "Face creation failed! Missing font file?" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_GlyphSlot glyphSlot = face->glyph;
	uint32_t atlasWidth = 0;
	uint32_t atlasHeight = 0;

	for (uint8_t i = 0; i < 128; ++i)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			std::cout << "Couldn't load glyph for character '" << static_cast<unsigned char>(i) << "'." << std::endl;
			continue;
		}

		atlasWidth += glyphSlot->bitmap.width;
		atlasHeight = std::max(atlasHeight, glyphSlot->bitmap.rows);
	}

	atlasSize = { atlasWidth, atlasHeight };

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &atlasTextureID);
	glBindTexture(GL_TEXTURE_2D, atlasTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	uint32_t xOffset = 0;
	uint32_t yOffset = 0;
	for (uint8_t i = 0; i < 128; ++i)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			std::cout << "Couldn't load glyph for character '" << static_cast<unsigned char>(i) << "'." << std::endl;
			continue;
		}
		//FT_GlyphSlot glyphSlot = face->glyph;

		glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, glyphSlot->bitmap.width, glyphSlot->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyphSlot->bitmap.buffer);

		Character c;
		c.advance = { glyphSlot->advance.x >> 6, glyphSlot->advance.y >> 6 };
		c.size = { glyphSlot->bitmap.width, glyphSlot->bitmap.rows };
		c.bearing = { glyphSlot->bitmap_left, glyphSlot->bitmap_top };
		c.atlasOffset = { xOffset, yOffset };

		xOffset += glyphSlot->bitmap.width;
		yOffset += 0; //for now, atlas is just one row

		characters.insert(std::make_pair(i, c));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(freetype);
}

Font::Font(Font&& other)
{
	characters.swap(other.characters);
	atlasSize = other.atlasSize;

	atlasTextureID = other.atlasTextureID;
	other.atlasTextureID = 0;
}

Font::~Font()
{
	if (atlasTextureID != 0) 
	{
		glDeleteTextures(1, &atlasTextureID);
	}
}