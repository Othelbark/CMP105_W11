#include "Game.h"

Game::Game(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) : Level(hwnd, in, gs, aud)
{
	view = window->getView();

	// initialise game objects
	player.setInput(input);
	player.setView(&view);
	player.setAudio(audio);
	player.setPosition(200, 300);
	player.setSize(sf::Vector2f(30, 42));
	player.setCollisionBox(0, 0, 30, 42);
	playerTexture.loadFromFile("gfx/MarioSheetT.png");
	player.setTexture(&playerTexture);



}

Game::~Game()
{
}

void Game::handleInput(float dt)
{
	// Close window on Escape pressed.
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}

	if (gameState->getCurrentState() != State::PAUSE)
	{
		player.handleInput(dt);
	}

	if (input->isKeyDown(sf::Keyboard::Space))
	{
		input->setKeyUp(sf::Keyboard::Space);
		if (gameState->getCurrentState() != State::PAUSE)
		{
			audio->getMusic()->pause();
			gameState->setCurrentState(State::PAUSE);
		}
		else
		{
			audio->getMusic()->play();
			gameState->setCurrentState(State::LEVEL);
		}
	}
}

void Game::update(float dt)
{
	player.update(dt);
	worldMap.checkMapCollision(&player);
}

void Game::render()
{
	beginDraw();
	window->draw(player);
	worldMap.drawMap(window);
	endDraw();
}
