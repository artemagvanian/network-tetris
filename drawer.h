//drawer.h is part of TetrixSTATIC
//Отвечает за отрисовку игрового цикла

#pragma once
#include "stdinclude.h"
#include "board.h"

using namespace sf;
using namespace std;

void Draw(Board BoardContainer, RenderWindow& window, int score) {

	Texture LightBlue_t, Blue_t, Orange_t, Yellow_t, Green_t, Magenta_t, Red_t, bg_t;

	bg_t.loadFromFile("redist/backgrounds/gamebg.png");
	LightBlue_t.loadFromFile("redist/blocks/LightBlue.png");
	Blue_t.loadFromFile("redist/blocks/Blue.png");
	Orange_t.loadFromFile("redist/blocks/Orange.png");
	Yellow_t.loadFromFile("redist/blocks/Yellow.png");
	Green_t.loadFromFile("redist/blocks/Green.png");
	Magenta_t.loadFromFile("redist/blocks/Magenta.png");
	Red_t.loadFromFile("redist/blocks/Red.png");

	window.clear();

	Sprite bg(bg_t);

	window.draw(bg);

	//Отрисовка поля
	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < YSIZE; j++)
		{
			Sprite cell;
			CellColor choice = BoardContainer.GetCellColor(i, j);
			int Player = BoardContainer.GetCellActive(i, j);
			switch (choice) {
			case Transparent:
				break;
			case LightBlue:
				cell.setTexture(LightBlue_t);
				cell.setPosition((float)(26 + i * 25), (float)(16 + j * 25));
				window.draw(cell);
				break;
			case Blue:
				cell.setTexture(Blue_t);
				cell.setPosition((float)(26 + i * 25), (float)(16 + j * 25));
				window.draw(cell);
				break;
			case Orange:
				cell.setTexture(Orange_t);
				cell.setPosition((float)(26 + i * 25), (float)(16 + j * 25));
				window.draw(cell);
				break;
			case Yellow:
				cell.setTexture(Yellow_t);
				cell.setPosition((float)(26 + i * 25), (float)(16 + j * 25));
				window.draw(cell);
				break;
			case Green:
				cell.setTexture(Green_t);
				cell.setPosition((float)(26 + i * 25), (float)(16 + j * 25));
				window.draw(cell);
				break;
			case Magenta:
				cell.setTexture(Magenta_t);
				cell.setPosition((float)(26 + i * 25), (float)(16 + j * 25));
				window.draw(cell);
				break;
			case Red:
				cell.setTexture(Red_t);
				cell.setPosition((float)(26 + i * 25), (float)(16 + j * 25));
				window.draw(cell);
				break;
			}
		}
	}

	Font font;
	if (!font.loadFromFile("redist/fonts/Arista.ttf")) {
		//cout << "Ошибка при загрузке шрифта!" << endl;
	}

	Text scoretext;
	scoretext.setFont(font);
	scoretext.setCharacterSize(24);
	scoretext.setPosition(190, 645);
	scoretext.setString(to_string(score));
	scoretext.setFillColor(Color::Black);
	window.draw(scoretext);

	window.display();
}