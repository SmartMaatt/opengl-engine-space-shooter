#pragma once

class Text;

class Font
{
	friend class Text;
public:
	Font(const std::string& fontFilePath, uint32_t size);
	Font(const Font&) = delete;
	Font(Font&&);
	~Font();
	Font& operator=(const Font&) = delete;

private:
	struct Character
	{
		glm::ivec2 advance;
		glm::ivec2 size;
		glm::ivec2 bearing;
		glm::ivec2 atlasOffset;
	};
	std::unordered_map<char, Character> characters;
	glm::vec2 atlasSize;

	GLuint atlasTextureID;
};

