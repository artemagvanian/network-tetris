//cell.h is part of TetrixSTATIC
//Содержит класс клетки и основные функции работы с ним

#pragma once

enum CellColor {Transparent = 0, LightBlue, Blue, Orange, Yellow, Green, Magenta, Red};

class Cell {
	bool isFilled;
	int isActive;
	CellColor color;
public:
	//Сеттеры
	void SetFilled(bool isFilled) {
		this->isFilled = isFilled;
	}

	void SetActive(int isActive) {
		this->isActive = isActive;
	}

	void SetColor(CellColor color) {
		this->color = color;
	}

	//Геттеры
	bool GetFilled() {
		return isFilled;
	}

	int GetActive() {
		return isActive;
	}

	CellColor GetColor() {
		return color;
	}

	//Конструктор по умолчанию
	Cell()
	{
		isFilled = false;
		isActive = false;
		color = Transparent;
	}

	//Очистка клетки
	void Clear() {
		isFilled = false;
		isActive = false;
		color = Transparent;
	}
	//Опервтор равно
	Cell& operator=(const Cell& right) {
		isFilled = right.isFilled;
		isActive = right.isActive;
		color = right.color;
		return *this;
	}
	//Конструктор копирования
	Cell (const Cell& right) {
		isFilled = right.isFilled;
		isActive = right.isActive;
		color = right.color;
	}
};