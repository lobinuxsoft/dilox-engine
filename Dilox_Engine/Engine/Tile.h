#pragma once
#include <glm/ext/vector_float2.hpp>
class Tile
{
public:
	char tileType;
	glm::vec2 position;
	glm::vec2 scale = { 1.0f,1.0f };
};

