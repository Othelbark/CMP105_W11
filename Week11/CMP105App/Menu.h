#pragma once
#include "Level.h"
class Menu : public Level
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Menu();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:
	//Things
	sf::Font font;
	sf::Text title;
	sf::Text info;
};

