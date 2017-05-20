//scoreboard.h is part of TetrixSTATIC
//Отвечает за вывод таблицы рекордов в графическом виде

#pragma once
#include "stdinclude.h"

using namespace std;
using namespace sf;

bool compare(pair<string, int> p1, pair<string, int> p2) {
	if (p1.second > p2.second)
		return true;
	return false;
}

void ShowScore() {
	RenderWindow window(VideoMode(750, 750), "Scoreboard", Style::Close);

	Image icon;
	icon.loadFromFile("redist/blocks/Blue.png");
	window.setIcon(24, 24, icon.getPixelsPtr());

	//Контейнеры для хранения данных
	static vector<pair<string, int>> scores;
	vector<Text> scoreTexts;
	vector<Text> nicknameTexts;
	vector<RectangleShape> scoreSprites;

	ifstream file;
	file.open("score.dat", ios::in);
	string first, second;

	//Считываем данные из файла
	if (!file) {

	}
	else {
		while (!file.eof()) {
			file >> first >> second;
			scores.push_back(make_pair(first, stoi(second)));
		}
	}

	file.close();

	sort(scores.begin(), scores.end(), compare);

	size_t sizeofboard = (scores.size() > 10) ? 10 : scores.size();

	//Обрезаем никнеймы до 10 символов
	for (size_t i = 0; i < scores.size(); i++)
	{
		if (scores[i].first.size() > 10) {
			scores[i].first.resize(10);
		}
	}

	//Парсим и запихиваем в контейнеры
	Font font;
	if (!font.loadFromFile("redist/fonts/Arista.ttf")) {
		//cout << "Ошибка при загрузке шрифта!" << endl;
	}
	for (size_t i = 0; i < sizeofboard; i++)
	{
		nicknameTexts.push_back(Text(scores[i].first, font, 30));
		nicknameTexts[i].setPosition(75, 155 + 55 * (float)i);
		nicknameTexts[i].setFillColor(Color::Black);
	}

	float x;
	for (size_t i = 0; i < sizeofboard; i++)
	{
		RectangleShape shape;
		shape.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
		shape.setPosition(375, 160 + 55 * (float)i);
		x = 3 * (float)scores[i].second / scores[0].second;
		shape.setSize(Vector2f(x, 30));
		shape.setOutlineColor(Color::White);
		shape.setOutlineThickness(2);
		scoreSprites.push_back(shape);
	}

	
	for (size_t i = 0; i < sizeofboard; i++)
	{
		scoreTexts.push_back(Text(to_string(scores[i].second), font, 30));
		scoreTexts[i].setPosition(275, 155 + 55 * (float)i);
		scoreTexts[i].setFillColor(Color::Black);
	}

	Texture background_t;
	background_t.loadFromFile("redist/backgrounds/scoreboardbg.png");
	Sprite background;
	background.setTexture(background_t);

	//Таймер и счётчик анимации
	Clock animation;
	int animationIterator = 2;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
				window.close();
			}
		}
		//Цикл анимации
		if ((animation.getElapsedTime().asMilliseconds() > 20) && animationIterator <= 100) {
			for (size_t i = 0; i < sizeofboard; i++)
			{
				scoreSprites[i].setSize(Vector2f(scoreSprites[i].getSize().x/(animationIterator - 1)*animationIterator, 30));
			}
			animationIterator++;
			animation.restart();
		}
		//Отрисовка всего
		window.clear();
		window.draw(background);
		for (size_t i = 0; i < sizeofboard; i++)
		{
			window.draw(nicknameTexts[i]);
			window.draw(scoreSprites[i]);
			window.draw(scoreTexts[i]);
		}
		window.display();
	}
}