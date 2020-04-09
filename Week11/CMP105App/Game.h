#pragma once
#include "Level.h"
#include "WorldMap.h"
#include "PlayerObject.h"
class Game : public Level
{
public:
	Game(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Game();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:
	// View Variable
	sf::View view;

	// GameObjects
	PlayerObject player;
	sf::Texture playerTexture;
	WorldMap worldMap;

};

