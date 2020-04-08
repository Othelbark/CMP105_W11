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

}

Menu::~Menu()
{
}

void Menu::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
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