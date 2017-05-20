//mbox.h is part of TetrixSTATIC
//Отвечает за создание MessageBox-ов с заданным содержимым
//Поддерживает работу в потоках

#pragma once
#include "stdinclude.h"

using namespace std;
using namespace sf;

void DropThread() {
	dropThread = true;
}

string mbox(string message, int delay = 0, size_t returnLength = 0, bool noSkip = false, bool manualDropping = false) {
	RenderWindow window(VideoMode(350, 200), "Message", Style::Close);

	//Подготовка к созданию mbox-а
	Image icon;
	icon.loadFromFile("redist/blocks/Blue.png");
	window.setIcon(24, 24, icon.getPixelsPtr());

	Texture background_t;
	background_t.loadFromFile("redist/backgrounds/messageboxbg.png");
	Sprite background;
	background.setTexture(background_t);

	string result;

	Font font;
	if (!font.loadFromFile("redist/fonts/Arista.ttf")) {
		//cout << "Ошибка при загрузке шрифта!" << endl;
	}

	Text MessageTitle(message, font, 40);
	MessageTitle.setPosition(Vector2f(20, 10));
	MessageTitle.setFillColor(Color::Black);

	Text ResultText("", font, 40);
	ResultText.setPosition(Vector2f(20, 100));
	ResultText.setFillColor(Color::Black);

	Clock clock;

	//Открытие цикла окна
	while (window.isOpen())
	{
		if (dropThread && manualDropping) {
			dropThread = false;
			window.close();
			return "";
		}
		Event event;
		while (window.pollEvent(event))
		{
			//Точки выхода
			if (event.type == Event::Closed) {
				window.close();
				return result;
			}
			if (!noSkip) {
				if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Return)) {
					window.close();
					return result;
				}
			}
			//Ввод текста
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode < 128 && event.text.unicode > 32)
				{
					if (result.size() < returnLength) {
						result += (char)event.text.unicode;
						ResultText.setString(result);
					}
				}
				//Стирание текста (8 == BS)
				if (event.text.unicode == 8) {
					if (result.size() > 0) {
						result.pop_back();
						ResultText.setString(result);
					}
				}
			}
		}
		if (delay != 0) {
			if (clock.getElapsedTime().asMilliseconds() >= delay)
				window.close();
		}

		window.clear();
		window.draw(background);
		window.draw(MessageTitle);
		window.draw(ResultText);
		window.display();
	}
}