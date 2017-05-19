#pragma once
#include "stdinclude.h"

using namespace sf;
using namespace std;

int CreateWindowMenu() {
	RenderWindow window(VideoMode(750, 750), "Menu", Style::Close);
	Texture background_t;
	background_t.loadFromFile("redist/backgrounds/menubg.png");
	Sprite background;
	background.setTexture(background_t);

	Image icon;
	icon.loadFromFile("redist/blocks/Blue.png");
	window.setIcon(24, 24, icon.getPixelsPtr());

	Font font;
	if (!font.loadFromFile("redist/fonts/Arista.ttf")) {
		//cout << "Ошибка при загрузке шрифта!" << endl;
	}
	vector<Text> menu;
	menu.resize(3);
	menu[0] = Text("Play", font, 60);
	menu[0].setPosition(Vector2f(200, 250));
	menu[1] = Text("Scoreboard", font, 60);
	menu[1].setPosition(Vector2f(200, 350));
	menu[2] = Text("Exit", font, 60);
	menu[2].setPosition(Vector2f(200, 450));

	for (size_t i = 0; i < 3; i++)
	{
		menu[i].setFillColor(Color::Black);
		menu[i].setOutlineColor(Color::White);
		menu[i].setOutlineThickness(2);
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
				window.close();
				return 3;
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (event.mouseButton.x >= 200 && event.mouseButton.y >= 250 && event.mouseButton.x <= 310 && event.mouseButton.y <= 310)
					{
						return 1;
					}
					if (event.mouseButton.x >= 200 && event.mouseButton.y >= 350 && event.mouseButton.x <= 490 && event.mouseButton.y <= 410)
					{
						return 2;
					}
					if (event.mouseButton.x >= 200 && event.mouseButton.y >= 450 && event.mouseButton.x <= 305 && event.mouseButton.y <= 510)
					{
						return 3;
					}
				}
			}
			if (event.type == Event::MouseMoved)
			{
				if (event.mouseMove.x >= 200 && event.mouseMove.y >= 250 && event.mouseMove.x <= 310 && event.mouseMove.y <= 310)
				{
					menu[0].setFillColor(Color(102, 0, 102));
				}
				else {
					menu[0].setFillColor(Color::Black);
				}
				if (event.mouseMove.x >= 200 && event.mouseMove.y >= 350 && event.mouseMove.x <= 490 && event.mouseMove.y <= 410)
				{
					menu[1].setFillColor(Color(102, 0, 102));
				}
				else {
					menu[1].setFillColor(Color::Black);
				}
				if (event.mouseMove.x >= 200 && event.mouseMove.y >= 450 && event.mouseMove.x <= 305 && event.mouseMove.y <= 510)
				{
					menu[2].setFillColor(Color(102, 0, 102));
				}
				else {
					menu[2].setFillColor(Color::Black);
				}
			}
		}
		window.clear();
		window.draw(background);
		for (size_t i = 0; i < 3; i++)
		{
			window.draw(menu[i]);
		}
		window.display();
	}
}