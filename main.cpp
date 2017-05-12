#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include "board.h"
#include "generator.h"
#include "drawer.h"
#include "network.h"

using namespace std;
using namespace sf;

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	int port = 3177;

	SetConsoleTitle("Logger");

	TcpSocket data;

	char mode = NULL;

	while (mode != 'S' && mode != 'C') {
		cout << "�� ������ ��� ������ (S/C): ";
		cin >> mode;
	}

	//�������� ������, ��������� ���������� � ��������
	if (mode == 'S') {
		IpAddress YourIp = IpAddress::getLocalAddress();

		cout << "��� IP: " << YourIp << endl << "�������� ��� ������� ������" << endl;

		TcpListener listener;

		size_t received;

		if (listener.listen(port) != Socket::Done)
		{
			cout << "��������� �����������..." << endl << "������ �� ����..." << endl;
			system("pause");
			return 0;
		}

		cout << "��� �������..." << endl;

		if (listener.accept(data) != Socket::Done)
		{
			cout << "��������� �����������..." << endl << "������ �� ����..." << endl;
			system("pause");
			return 0;
		}

		cout << "������ ������!" << endl;

		cout << "������������� ����������..." << endl;

		int key = rand();

		cout << "��� ���� " << key << " �������� ��� � ������ ������� ������..." << endl;

		data.send(&key, sizeof(int));

		bool answer = false;
		cout << "����� ��������� (0/1): ";
		cin >> answer;

		if (!answer) {
			cout << "��������� �����������..." << endl << "������ �� ����..." << endl;
			data.send(&answer, sizeof(bool));
			system("pause");
			return 0;
		}
		else {
			cout << "��� ������ ������� ������..." << endl;
			data.send(&answer, sizeof(bool));
			bool answer2 = false;
			data.receive(&answer2, sizeof(bool), received);
			if (!answer2) {
				cout << "��������� �����������..." << endl << "������ �� ����..." << endl;
				system("pause");
				return 0;
			}
		}
		cout << "������! �������� ����..." << endl;
		data.setBlocking(false);

	}
	else if (mode == 'C') {
		IpAddress ServerIp;

		cout << "������� IP �������: ";

		cin >> ServerIp;

		if (data.connect(ServerIp, port) != Socket::Done) {
			cout << "��������� �����������..." << endl << "������ �� ����..." << endl;
			system("pause");
			return 0;
		}

		size_t received;

		int key;

		data.receive(&key, sizeof(int), received);

		cout << "��� ���� " << key << " �������� ��� � ������ ������� ������..." << endl;

		bool answer = false;
		cout << "����� ��������� (0/1): ";
		cin >> answer;

		if (!answer) {
			cout << "��������� �����������..." << endl << "������ �� ����..." << endl;
			data.send(&answer, sizeof(bool));
			system("pause");
			return 0;
		}
		else {
			cout << "��� ������ ������� ������..." << endl;
			data.send(&answer, sizeof(bool));
			bool answer2;
			data.receive(&answer2, sizeof(bool), received);
			if (!answer2) {
				cout << "��������� �����������..." << endl << "������ �� ����..." << endl;
				system("pause");
				return 0;
			}
		}
		cout << "������! �������� ����..." << endl;
		data.setBlocking(false);
	}

	//���������� 
	Board MainBoard;
	RenderWindow window(VideoMode(550, 700), "Tetrix", Style::Close);
	Clock TurnClock1, TurnClock2;
	int score = 0;
	bool Move1 = true, Move2 = true;

	while (window.isOpen())
	{

		//���������� ������� ������
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
				window.close();
				cout << "#Game over" << endl;
				Packet p;
				p << QUIT;
				data.send(p);
				system("pause");
				return 0;
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right)) {
				if (mode == 'S') {
					MainBoard.MoveActiveRight(FIRST_PLAYER);
					Packet p;
					p << BOARD;
					MainBoard.SerializeIntoPacket(p, score);
					data.send(p);
				}
				else if (mode == 'C') {
					Packet p;
					p << MOVERIGHT;
					data.send(p);
				}
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left)) {
				if (mode == 'S') {
					MainBoard.MoveActiveLeft(FIRST_PLAYER);
					Packet p;
					p << BOARD;
					MainBoard.SerializeIntoPacket(p, score);
					data.send(p);
				}
				else if (mode == 'C') {
					Packet p;
					p << MOVELEFT;
					data.send(p);
				}
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Down)) {
				if (mode == 'S') {
					Move1 = MainBoard.MoveActiveDown(FIRST_PLAYER);
					TurnClock1.restart();
					Packet p;
					p << BOARD;
					MainBoard.SerializeIntoPacket(p, score);
					data.send(p);
				}
				else if (mode == 'C') {
					Packet p;
					p << MOVEDOWN;
					data.send(p);
				}
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Up)) {
				if (mode == 'S') {
					MainBoard.RotateActiveFigure(FIRST_PLAYER);
					Packet p;
					p << BOARD;
					MainBoard.SerializeIntoPacket(p, score);
					data.send(p);
				}
				else if (mode == 'C') {
					Packet p;
					p << ROTATE;
					data.send(p);
				}
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::LControl)) {
				if (mode == 'S') {
					MainBoard.BigMoveDown(FIRST_PLAYER);
					Move1 = false;
					Packet p;
					p << BOARD;
					MainBoard.SerializeIntoPacket(p, score);
					data.send(p);
				}
				else if (mode == 'C') {
					Packet p; 
					p << FULLMOVEDOWN;
					data.send(p);
				}
			}
		}

		//�������� ������ ���� �� �������, ���� ������ �������, ��������� �������� ���������� � ����� ���������
		if ((Move1 || Move2) && mode == 'S') {
			if (TurnClock1.getElapsedTime().asMilliseconds() >= 750) {
				TurnClock1.restart();
				Move1 = MainBoard.MoveActiveDown(FIRST_PLAYER);
				Packet p;
				p << BOARD;
				MainBoard.SerializeIntoPacket(p, score);
				data.send(p);
			}
			else if (TurnClock2.getElapsedTime().asMilliseconds() >= 750) {
				TurnClock2.restart();
				Move2 = MainBoard.MoveActiveDown(SECOND_PLAYER);
				Packet p;
				p << BOARD;
				MainBoard.SerializeIntoPacket(p, score);
				data.send(p);
			}
		}
		else if (mode == 'S') {
			MainBoard.Deactive();
			score += MainBoard.ClearStripes();
			if (!MainBoard.CheckGame()) {
				window.close();
				cout << "#Game over" << endl;
				Packet p;
				p << QUIT;
				data.send(p);
				system("pause");
				return 0;
			}
			GenerateFigure(MainBoard, FIRST_PLAYER);
			GenerateFigure(MainBoard, SECOND_PLAYER);
			Packet p;
			p << BOARD;
			MainBoard.SerializeIntoPacket(p, score);
			data.send(p);
			TurnClock1.restart();
			TurnClock2.restart();
			Move1 = true;
			Move2 = true;
		}

		//����������� ���������� ����� ����� ������� ��� ������� � �������
		Packet p;
		Socket::Status s = data.receive(p);
		if (s == Socket::Status::Done) {
			int action;
			p >> action;
			switch (action) {
			case MOVELEFT:
			{
				MainBoard.MoveActiveLeft(SECOND_PLAYER);
				Packet p1;
				p1 << BOARD;
				MainBoard.SerializeIntoPacket(p1, score);
				data.send(p1);
			}
			break;
			case MOVERIGHT:
			{
				MainBoard.MoveActiveRight(SECOND_PLAYER);
				Packet p1;
				p1 << BOARD;
				MainBoard.SerializeIntoPacket(p1, score);
				data.send(p1);
			}
			break;
			case MOVEDOWN:
			{
				Move2 = MainBoard.MoveActiveDown(SECOND_PLAYER);
				Packet p1;
				p1 << BOARD;
				MainBoard.SerializeIntoPacket(p1, score);
				data.send(p1);
				TurnClock2.restart();
			}
			break;
			case ROTATE:
			{
				MainBoard.RotateActiveFigure(SECOND_PLAYER);
				Packet p1;
				p1 << BOARD;
				MainBoard.SerializeIntoPacket(p1, score);
				data.send(p1);
			}
			break;
			case QUIT:
				window.close();
				cout << "#Game over" << endl;
				system("pause");
				return 0;
				break;
			case FULLMOVEDOWN:
			{
				MainBoard.BigMoveDown(SECOND_PLAYER);
				Move2 = false;
				Packet p1;
				p << BOARD;
				MainBoard.SerializeIntoPacket(p1, score);
				data.send(p1);
			}
			break;
			case BOARD:
				MainBoard.DeserializeFromPacket(p, score);
				break;
			}
		}
		Draw(MainBoard, window, score);
	}

	return 0;
}