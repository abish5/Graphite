#include <gppch.h>

#include "GameLevel.h"

GameLevel::GameLevel(std::shared_ptr<Graphite::Texture> tex)
	: m_Texture(tex)
{
}

void GameLevel::Load(const char* file, uint32_t levelWidth, uint32_t levelHeight)
{
	m_BGTiles.clear();
	uint32_t tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<uint32_t>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<uint32_t> row;
			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0) {
			init(tileData, levelWidth, levelHeight);
		}
	}
}

void GameLevel::init(std::vector<std::vector<uint32_t>> tileData, uint32_t levelWidth, uint32_t levelHeight)
{
	uint32_t height = tileData.size();
	uint32_t width = tileData[0].size();
	float unitWidth = 12 / static_cast<float>(width);
	float unitHeight = 12 / static_cast<float>(height);

	for (uint32_t y = 0; y < height; ++y)
	{
		for (uint32_t x = 0; x < width; ++x)
		{
			if (tileData[y][x] == 1)
			{
				glm::vec3 pos(x, height - (y + 1), 0);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject obj(pos, size, 0, 0);
				obj.m_IsSolid = true;
				m_BGTiles.push_back(obj);
			}
		}
	}
}

void GameLevel::DrawBackground(std::shared_ptr<Graphite::SpriteRenderer> renderer)
{
	renderer->MultiDraw(m_BGTiles, m_Texture);
}

void GameLevel::Draw(std::shared_ptr<Graphite::SpriteRenderer> renderer)
{
	for (uint32_t i = 0; i < m_BGTiles.size(); ++i)
	{
		m_BGTiles[i].Draw(renderer, m_Texture);
	}
}

bool GameLevel::IsCompleted()
{
	return false;
}
