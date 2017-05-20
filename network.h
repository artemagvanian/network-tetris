//network.h is part of TetrixSTATIC
//Отвечает за пересылку основных команд и игрового поля

#pragma once
#include "stdinclude.h"
#include "board.h"

using namespace sf;
using namespace std;

void SendSocketMessage(TcpSocket &sock, int command) {
	if (command >= 1 && command <= 7) {
		Packet p;
		p << command;
		sock.send(p);
	}
	else {
		//cout << "#Invalid command" << endl;
	}
}
void SendGameData(TcpSocket &sock, Board &board, int score) {
	Packet p;
	p << BOARD;
	board.SerializeIntoPacket(p, score);
	sock.send(p);
}