#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) : Level(hwnd, in, gs, aud)
{
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	title.setFont(font);
	title.setCharacterSize(48);
	title.setFillColor(sf::Color::Black);
	title.setPosition(10, 10);
	title.setString("Fake Mario");

	info.setFont(font);
	info.setCharacterSize(12);
	info.setFillColor(sf::Color::Black);
	info.setPosition(10, 100);
	info.setString("Press Enter to Start!");


	audio->addMusic("sfx/cantina.ogg", "cantina");
	audio->addSound("sfx/SMB_jump-small.ogg", "jump");
	audio->addSound("sfx/SMB_1-up.ogg", "up");

}

Menu::~Menu()
{
}

void Menu::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		audio->playMusicbyName("cantina");
		gameState->setCurrentState(State::LEVEL);
	}
}

void Menu::update(float dt)
{
}

void Menu::render()
{
	beginDraw();
	window->draw(title);
	window->draw(info);
	endDraw();
}