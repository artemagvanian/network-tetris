//board.h is part of TetrixSTATIC
//Содержит класс игрового поля и функции работы с ним

#pragma once
#include "stdinclude.h"
#include "cell.h"

using namespace std;
using namespace sf;

enum Tetramino { I = 0, J, L, O, S, T, Z };

class Board {
	array <array<Cell, YSIZE>, XSIZE> BoardContainer;
	Tetramino ActiveFigureType1, ActiveFigureType2;
	int CBlockX1, CBlockX2;
	int CBlockY1, CBlockY2;
	int RotateState1, RotateState2;
public:
	//Сериализация и десериализация доски
	void SerializeIntoPacket(Packet &p, int score) {
		for (size_t i = 0; i < XSIZE; i++)
		{
			for (size_t j = 0; j < YSIZE; j++)
			{
				p << (int)this->BoardContainer[i][j].GetColor();
			}
		}
		p << score;
	}

	void DeserializeFromPacket(Packet &p, int &score) {
		for (size_t i = 0; i < XSIZE; i++)
		{
			for (size_t j = 0; j < YSIZE; j++)
			{
				int a;
				p >> a;
				this->BoardContainer[i][j].SetColor((CellColor)a);
			}
		}
		p >> score;
	}

	//Блок сеттеров
	void SetCellColor(unsigned short x, unsigned short y, CellColor Color) {
		BoardContainer[x][y].SetColor(Color);
	}
	void SetCellFilled(unsigned short x, unsigned short y, bool filled) {
		BoardContainer[x][y].SetFilled(filled);
	}
	void SetCellActive(unsigned short x, unsigned short y, int active) {
		BoardContainer[x][y].SetActive(active);
	}
	void SetActiveFigureType1(Tetramino ActiveFigureType1) {
		this->ActiveFigureType1 = ActiveFigureType1;
	}
	void SetActiveFigureType2(Tetramino ActiveFigureType2) {
		this->ActiveFigureType2 = ActiveFigureType2;
	}
	void SetCBlockX1(int CBlockX1) {
		this->CBlockX1 = CBlockX1;
	}
	void SetCBlockX2(int CBlockX2) {
		this->CBlockX2 = CBlockX2;
	}
	void SetCBlockY1(int CBlockY1) {
		this->CBlockY1 = CBlockY1;
	}
	void SetCBlockY2(int CBlockY2) {
		this->CBlockY2 = CBlockY2;
	}
	void SetRotateState1(int RotateState1) {
		this->RotateState1 = RotateState1;
	}
	void SetRotateState2(int RotateState2) {
		this->RotateState2 = RotateState2;
	}

	//Блок геттеров
	CellColor GetCellColor(unsigned short x, unsigned short y) {
		return BoardContainer[x][y].GetColor();
	}
	bool GetCellFilled(unsigned short x, unsigned short y) {
		return BoardContainer[x][y].GetFilled();
	}
	int GetCellActive(unsigned short x, unsigned short y) {
		return BoardContainer[x][y].GetActive();
	}
	Tetramino GetActiveFigureType1() {
		return ActiveFigureType1;
	}
	Tetramino GetActiveFigureType2() {
		return ActiveFigureType2;
	}
	int GetCBlockX1() {
		return CBlockX1;
	}
	int GetCBlockX2() {
		return CBlockX2;
	}
	int GetCBlockY1() {
		return CBlockY1;
	}
	int GetCBlockY2() {
		return CBlockY2;
	}
	int GetRotateState1() {
		return RotateState1;
	}
	int GetRotateState2() {
		return RotateState2;
	}

	//Очистка линий и добавление очков
	unsigned int ClearStripes() {
		unsigned int points = 0;
		for (int i = 0; i < YSIZE; i++)
		{
			bool isStripe = true;
			for (int j = 0; j < XSIZE; j++)
			{
				if (BoardContainer[j][i].GetFilled()) {
					continue;
				}
				else {
					isStripe = false;
					break;
				}
			}
			if (isStripe) {
				points += 100;
				DeleteStripe(i);
			}
		}
		return points;
	}

	//Удаление линии
	void DeleteStripe(unsigned short y) {
		for (int i = (y - 1); i >= 0; i--)
		{
			for (int j = 0; j < XSIZE; j++)
			{
				BoardContainer[j][i + 1] = BoardContainer[j][i];
				BoardContainer[j][i].Clear();
			}
		}
	}

	//Сдвиг фигур игровка вниз
	bool MoveActiveDown(int Player) {
		bool StillMoving = true;
		bool active = false;
		for (int i = 0; i < XSIZE; i++)
		{
			for (int j = 0; j < YSIZE; j++)
			{
				if (BoardContainer[i][j].GetActive() == Player)
				{
					active = true;
					if (j + 1 < YSIZE)
					{
						if (!BoardContainer[i][j + 1].GetFilled() || (BoardContainer[i][j + 1].GetActive() == Player)) {
							continue;
						}
						else {
							StillMoving = false;
							break;
						}
					}
					else {
						StillMoving = false;
					}
				}
			}
		}
		if (StillMoving) {
			for (int i = 0; i < XSIZE; i++)
			{
				for (int j = YSIZE - 1; j >= 0; j--)
				{
					if (BoardContainer[i][j].GetActive() == Player)
					{
						BoardContainer[i][j + 1] = BoardContainer[i][j];
						BoardContainer[i][j].Clear();
					}
				}
			}
			if (Player == FIRST_PLAYER)
				CBlockY1++;
			else if (Player == SECOND_PLAYER)
				CBlockY2++;
		}
		if (StillMoving && !active) {
			StillMoving = false;
		}
		return StillMoving;
	}

	//Сдвиг фигур игрока влево
	void MoveActiveLeft(int Player) {
		bool StillMoving = true;
		for (int i = 0; i < XSIZE; i++)
		{
			for (int j = 0; j < YSIZE; j++)
			{
				if (BoardContainer[i][j].GetActive() == Player)
				{
					if (i - 1 >= 0) {
						if (!BoardContainer[i - 1][j].GetFilled() || (BoardContainer[i - 1][j].GetActive() == Player)) {
							continue;
						}
						else {
							StillMoving = false;
							break;
						}
					}
					else {
						StillMoving = false;
					}
				}
			}
		}
		if (StillMoving) {
			for (int i = 0; i < XSIZE; i++)
			{
				for (int j = 0; j < YSIZE; j++)
				{
					if (BoardContainer[i][j].GetActive() == Player)
					{
						BoardContainer[i - 1][j] = BoardContainer[i][j];
						BoardContainer[i][j].Clear();
					}
				}
			}
			if (Player == FIRST_PLAYER)
				CBlockX1--;
			else if (Player == SECOND_PLAYER)
				CBlockX2--;

		}
	}

	//Сдвиг фигур игрока вправо
	void MoveActiveRight(int Player) {
		bool StillMoving = true;
		for (int i = 0; i < XSIZE; i++)
		{
			for (int j = 0; j < YSIZE; j++)
			{
				if (BoardContainer[i][j].GetActive() == Player)
				{
					if (i + 1 < XSIZE) {
						if (!BoardContainer[i + 1][j].GetFilled() || (BoardContainer[i + 1][j].GetActive() == Player)) {
							continue;
						}
						else {
							StillMoving = false;
							break;
						}
					}
					else {
						StillMoving = false;
					}
				}

			}
		}
		if (StillMoving) {
			for (int i = XSIZE - 1; i >= 0; i--)
			{
				for (int j = 0; j < YSIZE; j++)
				{
					if (BoardContainer[i][j].GetActive() == Player)
					{
						BoardContainer[i + 1][j] = BoardContainer[i][j];
						BoardContainer[i][j].Clear();
					}
				}
			}
			if (Player == FIRST_PLAYER)
				CBlockX1++;
			else if (Player == SECOND_PLAYER)
				CBlockX2++;
		}
	}

	//Деактивация фигур игрока
	void Deactive() {
		for (int i = 0; i < XSIZE; i++)
		{
			for (int j = 0; j < YSIZE; j++)
			{
				BoardContainer[i][j].SetActive(0);

			}
		}
		//cout << "#DEACTIVATION!" << endl;
	}

	//Падение вниз фигуры
	void BigMoveDown(int player) {
		while (MoveActiveDown(player));
	}

	//Проверка клеток на активность
	bool isActiveCells() {
		for (int i = 0; i < XSIZE; i++)
		{
			for (int j = 0; j < YSIZE; j++)
			{
				if (BoardContainer[i][j].GetActive() > 0) {
					return true;
				}
			}
		}
		return false;
	}

	//Проверка, можем ли продолжать игру
	bool CheckGame() {
		for (int i = 0; i < XSIZE; i++)
		{
			if (BoardContainer[i][0].GetFilled() && BoardContainer[i][0].GetActive() == 0) {
				return false;
			}
		}
		return true;
	}

	//Поворот фигуры
	void RotateActiveFigure(int Player) {
		int ActiveFigureType = (Player == FIRST_PLAYER) ? ActiveFigureType1 : ActiveFigureType2;
		int RotateState = (Player == FIRST_PLAYER) ? RotateState1 : RotateState2;
		int CBlockX = (Player == FIRST_PLAYER) ? CBlockX1 : CBlockX2;
		int CBlockY = (Player == FIRST_PLAYER) ? CBlockY1 : CBlockY2;
		switch (ActiveFigureType) {
		case I:
			switch (RotateState) {
			case 0:
				if ((CBlockY + 2) < YSIZE && (CBlockY - 1 >= 0))
				{
					if (!GetCellFilled(CBlockX, CBlockY - 1) && !GetCellFilled(CBlockX, CBlockY + 1) && !GetCellFilled(CBlockX, CBlockY + 2))
					{
						BoardContainer[CBlockX][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX][CBlockY + 2] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX - 1][CBlockY].Clear();
						BoardContainer[CBlockX + 1][CBlockY].Clear();
						BoardContainer[CBlockX + 2][CBlockY].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 1;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 1;
					}
				}
				break;
			case 1:
				if ((CBlockX + 2) < XSIZE && (CBlockX - 1 >= 0))
				{
					if (!GetCellFilled(CBlockX - 1, CBlockY) && !GetCellFilled(CBlockX + 1, CBlockY) && !GetCellFilled(CBlockX + 2, CBlockY))
					{
						BoardContainer[CBlockX - 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 2][CBlockY] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX][CBlockY - 1].Clear();
						BoardContainer[CBlockX][CBlockY + 1].Clear();
						BoardContainer[CBlockX][CBlockY + 2].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 0;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 0;
					}
				}
				break;
			}
			break;
		case J:
			switch (RotateState) {
			case 0:
				if (CBlockY + 1 < YSIZE)
				{
					if (!GetCellFilled(CBlockX, CBlockY - 1) && !GetCellFilled(CBlockX, CBlockY + 1) && !GetCellFilled(CBlockX + 1, CBlockY - 1))
					{
						BoardContainer[CBlockX][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX + 1][CBlockY].Clear();
						BoardContainer[CBlockX - 1][CBlockY].Clear();
						BoardContainer[CBlockX - 1][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 1;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 1;
					}
				}
				break;
			case 1:
				if (CBlockX - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX - 1, CBlockY) && !GetCellFilled(CBlockX + 1, CBlockY) && !GetCellFilled(CBlockX + 1, CBlockY + 1))
					{
						BoardContainer[CBlockX - 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX + 1][CBlockY - 1].Clear();
						BoardContainer[CBlockX][CBlockY + 1].Clear();
						BoardContainer[CBlockX][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 2;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 2;
					}
				}
				break;
			case 2:
				if (CBlockY - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX, CBlockY - 1) && !GetCellFilled(CBlockX, CBlockY + 1) && !GetCellFilled(CBlockX - 1, CBlockY + 1))
					{
						BoardContainer[CBlockX][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX - 1][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX - 1][CBlockY].Clear();
						BoardContainer[CBlockX + 1][CBlockY].Clear();
						BoardContainer[CBlockX + 1][CBlockY + 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 3;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 3;
					}
				}
				break;
			case 3:
				if (CBlockX + 1 < XSIZE)
				{
					if (!GetCellFilled(CBlockX + 1, CBlockY) && !GetCellFilled(CBlockX - 1, CBlockY) && !GetCellFilled(CBlockX - 1, CBlockY - 1))
					{
						BoardContainer[CBlockX + 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX - 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX - 1][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX][CBlockY - 1].Clear();
						BoardContainer[CBlockX][CBlockY + 1].Clear();
						BoardContainer[CBlockX - 1][CBlockY + 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 0;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 0;
					}
				}
				break;
			}
			break;
		case L:
			switch (RotateState) {
			case 0:
				if (CBlockY + 1 < YSIZE)
				{
					if (!GetCellFilled(CBlockX, CBlockY - 1) && !GetCellFilled(CBlockX, CBlockY + 1) && !GetCellFilled(CBlockX + 1, CBlockY + 1))
					{
						BoardContainer[CBlockX][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX + 1][CBlockY].Clear();
						BoardContainer[CBlockX - 1][CBlockY].Clear();
						BoardContainer[CBlockX + 1][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 1;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 1;
					}
				}
				break;
			case 1:
				if (CBlockX - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX - 1, CBlockY) && !GetCellFilled(CBlockX + 1, CBlockY) && !GetCellFilled(CBlockX - 1, CBlockY + 1))
					{
						BoardContainer[CBlockX - 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX - 1][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX + 1][CBlockY + 1].Clear();
						BoardContainer[CBlockX][CBlockY + 1].Clear();
						BoardContainer[CBlockX][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 2;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 2;
					}
				}
				break;
			case 2:
				if (CBlockY - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX, CBlockY - 1) && !GetCellFilled(CBlockX, CBlockY + 1) && !GetCellFilled(CBlockX - 1, CBlockY - 1))
					{
						BoardContainer[CBlockX][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX - 1][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX - 1][CBlockY].Clear();
						BoardContainer[CBlockX + 1][CBlockY].Clear();
						BoardContainer[CBlockX - 1][CBlockY + 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 3;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 3;
					}
				}
				break;
			case 3:
				if (CBlockX + 1 < XSIZE)
				{
					if (!GetCellFilled(CBlockX + 1, CBlockY) && !GetCellFilled(CBlockX - 1, CBlockY) && !GetCellFilled(CBlockX + 1, CBlockY - 1))
					{
						BoardContainer[CBlockX + 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX - 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX][CBlockY - 1].Clear();
						BoardContainer[CBlockX][CBlockY + 1].Clear();
						BoardContainer[CBlockX - 1][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 0;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 0;
					}
				}
				break;
			}
			break;
		case O:
			break;
		case S:
			switch (RotateState) {
			case 0:
				if (CBlockY + 1 < YSIZE)
				{
					if (!GetCellFilled(CBlockX + 1, CBlockY) && !GetCellFilled(CBlockX + 1, CBlockY + 1))
					{
						BoardContainer[CBlockX + 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX - 1][CBlockY].Clear();
						BoardContainer[CBlockX + 1][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 1;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 1;
					}
				}
				break;
			case 1:
				if (CBlockX - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX - 1, CBlockY) && !GetCellFilled(CBlockX + 1, CBlockY - 1))
					{
						BoardContainer[CBlockX - 1][CBlockY] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX + 1][CBlockY].Clear();
						BoardContainer[CBlockX + 1][CBlockY + 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 0;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 0;
					}
				}
				break;
			}
			break;
		case T:
			switch (RotateState) {
			case 0:
				if (CBlockY + 1 < YSIZE)
				{
					if (!GetCellFilled(CBlockX, CBlockY + 1))
					{
						BoardContainer[CBlockX][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX - 1][CBlockY].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 1;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 1;
					}
				}
				break;
			case 1:
				if (CBlockX - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX - 1, CBlockY))
					{
						BoardContainer[CBlockX - 1][CBlockY] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 2;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 2;
					}
				}
				break;
			case 2:
				if (CBlockY - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX, CBlockY - 1))
					{
						BoardContainer[CBlockX][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX + 1][CBlockY].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 3;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 3;
					}
				}
				break;
			case 3:
				if (CBlockX + 1 < XSIZE)
				{
					if (!GetCellFilled(CBlockX + 1, CBlockY))
					{
						BoardContainer[CBlockX + 1][CBlockY] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX][CBlockY + 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 0;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 0;
					}
				}
				break;
			}
			break;
		case Z:
			switch (RotateState) {
			case 0:
				if (CBlockY + 1 < YSIZE)
				{
					if (!GetCellFilled(CBlockX, CBlockY + 1) && !GetCellFilled(CBlockX + 1, CBlockY - 1))
					{
						BoardContainer[CBlockX][CBlockY + 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX + 1][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX - 1][CBlockY - 1].Clear();
						BoardContainer[CBlockX][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 1;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 1;
					}
				}
				break;
			case 1:
				if (CBlockX - 1 >= 0)
				{
					if (!GetCellFilled(CBlockX - 1, CBlockY - 1) && !GetCellFilled(CBlockX, CBlockY - 1))
					{
						BoardContainer[CBlockX - 1][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];
						BoardContainer[CBlockX][CBlockY - 1] = BoardContainer[CBlockX][CBlockY];

						BoardContainer[CBlockX][CBlockY + 1].Clear();
						BoardContainer[CBlockX + 1][CBlockY - 1].Clear();

						if (Player == FIRST_PLAYER)
							RotateState1 = 0;
						else if (Player == SECOND_PLAYER)
							RotateState2 = 0;
					}
				}
				break;
			}
			break;
		}
	}
};