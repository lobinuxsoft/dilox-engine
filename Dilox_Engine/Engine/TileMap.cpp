#include "dgepch.h"
#include "TileMap.h"


TileMap::TileMap(static const char* s_MapTiles)
{
	m_MapWidth = s_MapWidth;

	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	m_Atlas = DiloxGE::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_GrassTile = DiloxGE::SubTexture2D::CreateFromCoords(m_Atlas, { 1,11 }, { 128,128 }, { 1,1 });
	m_WaterTile = DiloxGE::SubTexture2D::CreateFromCoords(m_Atlas, { 11,11 }, { 128,128 }, { 1,1 });
}

TileMap::~TileMap()
{

}

void TileMap::DrawTileMap()
{
	for (int y = 0; y < m_MapHeight; y++)
	{
		for (int x = 0; x < m_MapWidth; x++)
		{
			//Esto deberia ir en una funcion de CreateTileMap
			auxTile[y][x].tileType = s_MapTiles[x + y * m_MapWidth];

			if (s_TextureMap.find(auxTile[y][x].tileType) != s_TextureMap.end())
			{
				tileTexture = s_TextureMap[auxTile[y][x].tileType];
			}
			else
			{
				tileTexture = m_GrassTile;
			}

			//Esto deberia ir en una funcion de CreateTileMap
			auxTile[y][x].position = { m_MapWidth - x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f };

			DiloxGE::Renderer2D::DrawQuad(auxTile[y][x].position, { 1,1 }, tileTexture, 1.0f, { 1.0f,1.0f,1.0f,1.0f });
		}
	}
}
