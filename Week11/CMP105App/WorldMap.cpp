#include "WorldMap.h"

WorldMap::WorldMap()
{
	//load texture
	tileMap.loadTexture("gfx/marioTiles.png");


	//create tileset
	GameObject tile;
	std::vector<GameObject> tiles;

	for (int i = 0; i < 10; i++)
	{
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tiles.push_back(tile);
	}

	tiles[0].setCollider(false);
	tiles[0].setTextureRect(sf::IntRect(187, 51, 16, 16));
	tiles[1].setTextureRect(sf::IntRect(0, 0, 16, 16));
	tiles[2].setTextureRect(sf::IntRect(17, 0, 16, 16));
	tiles[3].setTextureRect(sf::IntRect(34, 0, 16, 16));
	tiles[4].setTextureRect(sf::IntRect(0, 17, 16, 16));
	tiles[5].setTextureRect(sf::IntRect(17, 17, 16, 16));
	tiles[6].setTextureRect(sf::IntRect(34, 17, 16, 16));
	tiles[7].setTextureRect(sf::IntRect(0, 34, 16, 16));
	tiles[8].setTextureRect(sf::IntRect(17, 34, 16, 16));
	tiles[9].setTextureRect(sf::IntRect(34, 34, 16, 16));

	tileMap.setTileSet(tiles);


	//create map
	sf::Vector2u mapSize(12, 6);

	std::vector<int> map = {
		1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 1, 3,
		4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 4, 6,
		4, 5, 6, 0, 0, 0, 0, 0, 1, 3, 4, 6,
		4, 5, 6, 0, 0, 0, 0, 0, 7, 9, 4, 6,
		4, 5, 6, 1, 3, 1, 2, 3, 0, 0, 4, 6,
		7, 8, 9, 7, 9, 7, 8, 9, 0, 0, 7, 9
	};

	tileMap.setTileMap(map, mapSize);
	tileMap.setPosition(sf::Vector2f(0, 408));
	tileMap.buildLevel();
}

WorldMap::~WorldMap()
{
}

void WorldMap::drawMap(sf::RenderWindow* window)
{
	tileMap.render(window);
}

void WorldMap::checkMapCollision(GameObject* object)
{
	std::vector<GameObject>* world = tileMap.getLevel();
	for (int i = 0; i < (int)world->size(); i++)
	{
		// if collision check should occur
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(object, &(*world)[i]))
			{
				object->collisionResponse(&(*world)[i]);
			}
		}
	}
}
