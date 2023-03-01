#pragma once
#include <Engine/Renderer/Renderer2D.h>
#include "Tile.h"

class TileMap
{
public:
	TileMap(static const char* s_MapTiles);
	~TileMap();

	void DrawTileMap();

	DiloxGE::Ref<DiloxGE::Texture2D> m_Atlas;

	DiloxGE::Ref<DiloxGE::SubTexture2D> m_GrassTile;
	DiloxGE::Ref<DiloxGE::SubTexture2D> m_WaterTile;

	Tile auxTile[32][32];

private:
	static const int s_MapWidth = 24;

	int m_MapWidth, m_MapHeight;

	static const char* s_MapTiles;

	std::unordered_map<char, DiloxGE::Ref<DiloxGE::SubTexture2D>> s_TextureMap;
};

