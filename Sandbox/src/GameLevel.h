#include "GameObject.h"

class GameLevel {
public:
	GameLevel(std::shared_ptr<Graphite::Texture> tex);
	void Load(const char *file, uint32_t levelWidth, uint32_t levelHeight);
	void DrawBackground(std::shared_ptr<Graphite::SpriteRenderer> renderer);
	void Draw(std::shared_ptr<Graphite::SpriteRenderer> renderer);
	bool IsCompleted();
public:
	std::vector<GameObject> m_BGTiles;
private:
	std::shared_ptr<Graphite::Texture> m_Texture;
	void init(std::vector<std::vector<uint32_t>> tileData,
			uint32_t levelWidth, uint32_t levelHeight);
};