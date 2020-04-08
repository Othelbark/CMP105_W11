#pragma once
#include "Framework/TileMap.h"
#include "Framework/Collision.h"

class WorldMap
{
public:
	WorldMap();
	~WorldMap();

	void drawMap(sf::RenderWindow* window);
	void checkMapCollision(GameObject* object);

protected:
	TileMap tileMap;
};

