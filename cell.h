#pragma once

enum CellColor {Transparent = 0, LightBlue, Blue, Orange, Yellow, Green, Magenta, Red};

class Cell {
	bool isFilled;
	int isActive;
	CellColor color;
public:

	void SetFilled(bool isFilled) {
		this->isFilled = isFilled;
	}

	void SetActive(int isActive) {
		this->isActive = isActive;
	}

	void SetColor(CellColor color) {
		this->color = color;
	}

	bool GetFilled() {
		return isFilled;
	}

	int GetActive() {
		return isActive;
	}

	CellColor GetColor() {
		return color;
	}

	Cell()
	{
		isFilled = false;
		isActive = false;
		color = Transparent;
	}
	void Clear() {
		isFilled = false;
		isActive = false;
		color = Transparent;
	}
	Cell& operator=(const Cell& right) {
		isFilled = right.isFilled;
		isActive = right.isActive;
		color = right.color;
		return *this;
	}
	Cell (const Cell& right) {
		isFilled = right.isFilled;
		isActive = right.isActive;
		color = right.color;
	}
};