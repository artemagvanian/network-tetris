//generator.h is part of TetrixSTATIC
//Отвечает за генерацию поля 

#pragma once
#include "stdinclude.h"
#include "board.h"

short GenerateFigure(Board& BoardContainer, int Player) {
	short choice = rand() % 7;
	int push = (Player == SECOND_PLAYER) ? 11 : 0;

	/*
	0: ****

	1: *
	   ***

	2:   *
	   ***

	3: **
	   **

	4:  **
	   **

	5:  *
	   ***

	6: **
		**
	*/

	//cout << "#" << "Generating figure " << choice << " for player " << Player << endl;

	//Генерация клеток
	switch (choice) {
	case 0:
		BoardContainer.SetCellColor(3 + push, 1, LightBlue);
		BoardContainer.SetCellActive(3 + push, 1, Player);
		BoardContainer.SetCellFilled(3 + push, 1, true);
		BoardContainer.SetCellColor(4 + push, 1, LightBlue);
		BoardContainer.SetCellActive(4 + push, 1, Player);
		BoardContainer.SetCellFilled(4 + push, 1, true);
		BoardContainer.SetCellColor(5 + push, 1, LightBlue);
		BoardContainer.SetCellActive(5 + push, 1, Player);
		BoardContainer.SetCellFilled(5 + push, 1, true);
		BoardContainer.SetCellColor(6 + push, 1, LightBlue);
		BoardContainer.SetCellActive(6 + push, 1, Player);
		BoardContainer.SetCellFilled(6 + push, 1, true);
		if (Player == FIRST_PLAYER) {
			BoardContainer.SetActiveFigureType1(I);
			BoardContainer.SetRotateState1(0);
			BoardContainer.SetCBlockX1(4 + push);
			BoardContainer.SetCBlockY1(1);
		}
		else if (Player == SECOND_PLAYER) {
			BoardContainer.SetActiveFigureType2(I);
			BoardContainer.SetRotateState2(0);
			BoardContainer.SetCBlockX2(4 + push);
			BoardContainer.SetCBlockY2(1);
		}
		
		break;
	case 1:
		BoardContainer.SetCellColor(3 + push, 0, Blue);
		BoardContainer.SetCellActive(3 + push, 0, Player);
		BoardContainer.SetCellFilled(3 + push, 0, true);
		BoardContainer.SetCellColor(3 + push, 1, Blue);
		BoardContainer.SetCellActive(3 + push, 1, Player);
		BoardContainer.SetCellFilled(3 + push, 1, true);
		BoardContainer.SetCellColor(4 + push, 1, Blue);
		BoardContainer.SetCellActive(4 + push, 1, Player);
		BoardContainer.SetCellFilled(4 + push, 1, true);
		BoardContainer.SetCellColor(5 + push, 1, Blue);
		BoardContainer.SetCellActive(5 + push, 1, Player);
		BoardContainer.SetCellFilled(5 + push, 1, true);
		if (Player == FIRST_PLAYER) {
			BoardContainer.SetActiveFigureType1(J);
			BoardContainer.SetRotateState1(0);
			BoardContainer.SetCBlockX1(4 + push);
			BoardContainer.SetCBlockY1(1);
		}
		else if (Player == SECOND_PLAYER) {
			BoardContainer.SetActiveFigureType2(J);
			BoardContainer.SetRotateState2(0);
			BoardContainer.SetCBlockX2(4 + push);
			BoardContainer.SetCBlockY2(1);
		}
		break;
	case 2:
		BoardContainer.SetCellColor(5 + push, 0, Orange);
		BoardContainer.SetCellActive(5 + push, 0, Player);
		BoardContainer.SetCellFilled(5 + push, 0, true);
		BoardContainer.SetCellColor(3 + push, 1, Orange);
		BoardContainer.SetCellActive(3 + push, 1, Player);
		BoardContainer.SetCellFilled(3 + push, 1, true);
		BoardContainer.SetCellColor(4 + push, 1, Orange);
		BoardContainer.SetCellActive(4 + push, 1, Player);
		BoardContainer.SetCellFilled(4 + push, 1, true);
		BoardContainer.SetCellColor(5 + push, 1, Orange);
		BoardContainer.SetCellActive(5 + push, 1, Player);
		BoardContainer.SetCellFilled(5 + push, 1, true);
		if (Player == FIRST_PLAYER) {
			BoardContainer.SetActiveFigureType1(L);
			BoardContainer.SetRotateState1(0);
			BoardContainer.SetCBlockX1(4 + push);
			BoardContainer.SetCBlockY1(1);
		}
		else if (Player == SECOND_PLAYER) {
			BoardContainer.SetActiveFigureType2(L);
			BoardContainer.SetRotateState2(0);
			BoardContainer.SetCBlockX2(4 + push);
			BoardContainer.SetCBlockY2(1);
		}
		break;
	case 3:
		BoardContainer.SetCellColor(3 + push, 0, Yellow);
		BoardContainer.SetCellActive(3 + push, 0, Player);
		BoardContainer.SetCellFilled(3 + push, 0, true);
		BoardContainer.SetCellColor(4 + push, 0, Yellow);
		BoardContainer.SetCellActive(4 + push, 0, Player);
		BoardContainer.SetCellFilled(4 + push, 0, true);
		BoardContainer.SetCellColor(3 + push, 1, Yellow);
		BoardContainer.SetCellActive(3 + push, 1, Player);
		BoardContainer.SetCellFilled(3 + push, 1, true);
		BoardContainer.SetCellColor(4 + push, 1, Yellow);
		BoardContainer.SetCellActive(4 + push, 1, Player);
		BoardContainer.SetCellFilled(4 + push, 1, true);
		if (Player == FIRST_PLAYER) {
			BoardContainer.SetActiveFigureType1(O);
			BoardContainer.SetRotateState1(0);
			BoardContainer.SetCBlockX1(3 + push);
			BoardContainer.SetCBlockY1(0);
		}
		else if (Player == SECOND_PLAYER) {
			BoardContainer.SetActiveFigureType2(O);
			BoardContainer.SetRotateState2(0);
			BoardContainer.SetCBlockX2(3 + push);
			BoardContainer.SetCBlockY2(0);
		}
		break;
	case 4:
		BoardContainer.SetCellColor(5 + push, 0, Green);
		BoardContainer.SetCellActive(5 + push, 0, Player);
		BoardContainer.SetCellFilled(5 + push, 0, true);
		BoardContainer.SetCellColor(4 + push, 0, Green);
		BoardContainer.SetCellActive(4 + push, 0, Player);
		BoardContainer.SetCellFilled(4 + push, 0, true);
		BoardContainer.SetCellColor(3 + push, 1, Green);
		BoardContainer.SetCellActive(3 + push, 1, Player);
		BoardContainer.SetCellFilled(3 + push, 1, true);
		BoardContainer.SetCellColor(4 + push, 1, Green);
		BoardContainer.SetCellActive(4 + push, 1, Player);
		BoardContainer.SetCellFilled(4 + push, 1, true);
		if (Player == FIRST_PLAYER) {
			BoardContainer.SetActiveFigureType1(S);
			BoardContainer.SetRotateState1(0);
			BoardContainer.SetCBlockX1(4 + push);
			BoardContainer.SetCBlockY1(1);
		}
		else if (Player == SECOND_PLAYER) {
			BoardContainer.SetActiveFigureType2(S);
			BoardContainer.SetRotateState2(0);
			BoardContainer.SetCBlockX2(4 + push);
			BoardContainer.SetCBlockY2(1);
		}
		break;
	case 5:
		BoardContainer.SetCellColor(4 + push, 0, Magenta);
		BoardContainer.SetCellActive(4 + push, 0, Player);
		BoardContainer.SetCellFilled(4 + push, 0, true);
		BoardContainer.SetCellColor(3 + push, 1, Magenta);
		BoardContainer.SetCellActive(3 + push, 1, Player);
		BoardContainer.SetCellFilled(3 + push, 1, true);
		BoardContainer.SetCellColor(4 + push, 1, Magenta);
		BoardContainer.SetCellActive(4 + push, 1, Player);
		BoardContainer.SetCellFilled(4 + push, 1, true);
		BoardContainer.SetCellColor(5 + push, 1, Magenta);
		BoardContainer.SetCellActive(5 + push, 1, Player);
		BoardContainer.SetCellFilled(5 + push, 1, true);
		if (Player == FIRST_PLAYER) {
			BoardContainer.SetActiveFigureType1(T);
			BoardContainer.SetRotateState1(0);
			BoardContainer.SetCBlockX1(4 + push);
			BoardContainer.SetCBlockY1(1);
		}
		else if (Player == SECOND_PLAYER) {
			BoardContainer.SetActiveFigureType2(T);
			BoardContainer.SetRotateState2(0);
			BoardContainer.SetCBlockX2(4 + push);
			BoardContainer.SetCBlockY2(1);
		}
		break;
	case 6:
		BoardContainer.SetCellColor(3 + push, 0, Red);
		BoardContainer.SetCellActive(3 + push, 0, Player);
		BoardContainer.SetCellFilled(3 + push, 0, true);
		BoardContainer.SetCellColor(4 + push, 0, Red);
		BoardContainer.SetCellActive(4 + push, 0, Player);
		BoardContainer.SetCellFilled(4 + push, 0, true);
		BoardContainer.SetCellColor(5 + push, 1, Red);
		BoardContainer.SetCellActive(5 + push, 1, Player);
		BoardContainer.SetCellFilled(5 + push, 1, true);
		BoardContainer.SetCellColor(4 + push, 1, Red);
		BoardContainer.SetCellActive(4 + push, 1, Player);
		BoardContainer.SetCellFilled(4 + push, 1, true);
		if (Player == FIRST_PLAYER) {
			BoardContainer.SetActiveFigureType1(Z);
			BoardContainer.SetRotateState1(0);
			BoardContainer.SetCBlockX1(4 + push);
			BoardContainer.SetCBlockY1(1);
		}
		else if (Player == SECOND_PLAYER) {
			BoardContainer.SetActiveFigureType2(Z);
			BoardContainer.SetRotateState2(0);
			BoardContainer.SetCBlockX2(4 + push);
			BoardContainer.SetCBlockY2(1);
		}
		break;
	}
	return choice;
}